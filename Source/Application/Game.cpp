#include "Game.h"

#include "Input.h"

Game::Game()
	: m_window(Window(1280, 720, "MineClone", true))
{
}

void Game::run()
{
	float beginTime = glfwGetTime();
	float endTime;
	float dt = 0.016f;
	while (!m_window.shouldClose())
	{
		m_window.pollEvents();
		m_window.clear();

		// Game goes here

		m_window.swapBuffers();
		endTime = glfwGetTime();
		dt = endTime - beginTime;
		beginTime = endTime;

		if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
		{
			m_window.close();
		}
	}
}
