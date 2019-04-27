#include "construction-system.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

#include "core/constants.hpp"
#include "events/click.hpp"
#include "components/transform.hpp"

ConstructionSystem::ConstructionSystem(entt::DefaultRegistry& registry, EventEmitter& emitter, Map& map, b2World& physicWorld)
: System(registry), m_emitter(emitter), m_map(map), m_towerFactory(registry, physicWorld)
{
	m_emitter.on<evnt::Click>([this](const evnt::Click& event, EventEmitter& emitter) {
		glm::vec2 tilePosition = this->m_map.projToGrid(event.mousePos.x, event.mousePos.y);
		unsigned int entityId = this->m_map.getTile(tilePosition.x, tilePosition.y);
		cmpt::Transform trans = this->m_registry.get<cmpt::Transform>(entityId);
		this->m_towerFactory.create(trans.position.x, trans.position.y);
	});
}

