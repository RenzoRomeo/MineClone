#pragma once

#include "../core.h"

#include "Window.h"
#include "../World/World.h"
#include "../Renderer/Renderer.h"

class Game
{
public:
	Game();

	void run();

private:
	Window m_window;
	World& m_world;
	Renderer m_renderer;
};