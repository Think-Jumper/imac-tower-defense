#pragma once

#include <NsGui/IView.h>
#include <NsRender/GLFactory.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/IRenderer.h>
#include <memory>

#include "i-game-state.hpp"
#include "events/left-click-down.hpp"
#include "events/left-click-up.hpp"
#include "gui/level-hud.hpp"

class Game; // Forward declaration

class LevelState : public IGameState {
public:
	LevelState(Game& game);
	virtual ~LevelState();

	void enter() override;
	void update(float deltatime) override;
	void exit() override;

	// Events
	void onLeftClickUp(const evnt::LeftClickUp& event) override;
	void onLeftClickDown(const evnt::LeftClickDown& event) override;

private:
	Noesis::Ptr<Noesis::FrameworkElement> m_xaml;
	Noesis::IView* m_ui;
	LevelHud m_levelHud;
};
