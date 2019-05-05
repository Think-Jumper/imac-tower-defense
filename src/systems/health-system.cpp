#include "health-system.hpp"

#include <spdlog/spdlog.h>

#include "events/enemy-dead.hpp"
#include "components/health.hpp"
#include "components/transform.hpp"

HealthSystem::HealthSystem(entt::DefaultRegistry& registry, EventEmitter& emitter)
: ISystem(registry), m_emitter(emitter) {}

void HealthSystem::connectEvents() {
	auto connection = m_emitter.on<evnt::ProjectileHit>([this](const evnt::ProjectileHit & event, EventEmitter & emitter) {
		cmpt::Health& health = m_registry.get<cmpt::Health>(event.targetId);
		health.current -= event.damage;
		if (health.current <= 0.01f) {
			m_emitter.publish<evnt::EnnemyDead>(event.position);
			m_registry.destroy(event.targetId);
		}
	});
	m_projectileCon = std::make_unique<entt::Emitter<EventEmitter>::Connection<evnt::ProjectileHit>>(connection);
}

void HealthSystem::disconnectEvents() {
	m_emitter.erase(*m_projectileCon);
	m_projectileCon.reset();
}

void HealthSystem::update(float deltatime) {

}
