#include "attack-system.hpp"

#include <math.h>
#include <spdlog/spdlog.h>

#include "core/tags.hpp"
#include "components/targeting.hpp"
#include "components/look-at.hpp"
#include "components/shoot-at.hpp"
#include "services/locator.hpp"
#include "services/debug-draw/i-debug-draw.hpp"

AttackSystem::AttackSystem(entt::DefaultRegistry& registry) : ISystem(registry), m_projectileFactory(registry) {}

void AttackSystem::update(float deltatime) {
	//Look at target
	m_registry.view<cmpt::Targeting, cmpt::Transform , cmpt::LookAt>().each([this](auto entity, cmpt::Targeting & targeting, cmpt::Transform & transform, cmpt::LookAt lookAt) {
		if ( m_registry.valid(targeting.targetId) ) {
			glm::vec2 direction = m_registry.get<cmpt::Transform>(targeting.targetId).position - transform.position;
			transform.rotation = atan2(direction.y, direction.x);
		}
	});

	//Shoot at target
	m_registry.view<cmpt::Targeting, cmpt::Transform, cmpt::ShootAt>().each([this](auto entity, cmpt::Targeting & targeting, cmpt::Transform & transform, cmpt::ShootAt & shootAt) {
		if (m_registry.valid(targeting.targetId) ) {
			if (shootAt.timer == shootAt.loadingTime) {
				m_projectileFactory.create(transform.position, targeting.targetId);
				shootAt.timer = 0;
			}
			else {
				shootAt.timer++;
			}
		}
	});

	//Pick a new target if current one is out of range or dead
	m_registry.view<cmpt::Transform, cmpt::Trigger, cmpt::Targeting>().each([this](auto entity1, cmpt::Transform & transform1, cmpt::Trigger & trigger1, cmpt::Targeting & targeting) {
		IDebugDraw& dd = entt::ServiceLocator<IDebugDraw>::ref();
		dd.DrawCircle(b2Vec2(transform1.position.x, transform1.position.y), trigger1.radius, b2Color(1, 0, 0, 0.5f));

		if ( !m_registry.valid(targeting.targetId) || !isInRange(transform1, trigger1, targeting.targetId)) {
			targeting.targetId = -1;
			m_registry.view<cmpt::Transform, cmpt::Trigger, entityTag::Enemy>().each([this, entity1, transform1, trigger1, &targeting](auto entity2, cmpt::Transform & transform2, cmpt::Trigger & trigger2, auto) {
				if ( isInRange(transform1,trigger1,transform2,trigger2) ) {
					targeting.targetId = entity2;
				}
			});
		}
	});
}

void AttackSystem::connectEvents() {

}

void AttackSystem::disconnectEvents() {

}

bool AttackSystem::isInRange(cmpt::Transform transform1, cmpt::Trigger trigger1, cmpt::Transform transform2, cmpt::Trigger trigger2) {
	const glm::vec2 deltaPos = transform2.position - transform1.position;
	const float distanceSq = deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y;
	const float radii = trigger1.radius + trigger2.radius;
	return distanceSq <= radii * radii;
}

bool AttackSystem::isInRange(cmpt::Transform transform1, cmpt::Trigger trigger1, unsigned int targetId) {
	cmpt::Transform transform2 = m_registry.get<cmpt::Transform>(targetId);
	cmpt::Trigger trigger2 = m_registry.get<cmpt::Trigger>(targetId);
	return isInRange(transform1, trigger1, transform2, trigger2);
}