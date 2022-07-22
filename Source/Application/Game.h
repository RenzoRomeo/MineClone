#pragma once

#include "../core.h"

#include "Window.h"

class Game
{
public:
	Game();

	void run();

private:
	Window m_window;
};