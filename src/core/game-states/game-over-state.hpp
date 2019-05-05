#pragma once

#include <NsGui/IView.h>
#include <NsRender/GLFactory.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/IRenderer.h>

#include "systems/render-system.hpp"
#include "systems/movement-system.hpp"
#include "systems/animation-system.hpp"
#include "systems/construction-system.hpp"
#include "systems/wave-system.hpp"
#include "systems/attack-system.hpp"
#include "systems/health-system.hpp"
#include "events/handlers/event-emitter.hpp"
#include "events/left-click-down.hpp"
#include "events/left-click-up.hpp"
#include "i-game-state.hpp"
#include "gui/game-over.hpp"

class GameOverState : public IGameState {
public:
	GameOverState(EventEmitter& emitter, AnimationSystem& animationSystem, MovementSystem& movementSystem, AttackSystem& attackSystem, RenderSystem& renderSystem);
	virtual ~GameOverState();

	void onEnter() override;
	void update(float deltatime) override;
	void onExit() override;

private:
	Noesis::Ptr<Noesis::FrameworkElement> m_xaml;
	Noesis::IView* m_ui;
	GameOver m_gameOver;

	entt::Emitter<EventEmitter>::Connection<evnt::LeftClickDown>* m_clickDownCon;
	entt::Emitter<EventEmitter>::Connection<evnt::LeftClickUp>* m_clickUpCon;
};
