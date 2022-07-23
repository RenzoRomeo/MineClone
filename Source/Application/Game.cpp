#include "Game.h"

#include "Input.h"
#include "../OpenGL/Vbo.h"
#include "../OpenGL/Vao.h"
#include "../OpenGL/Ebo.h"
#include "../OpenGL/VboLayout.h"
#include "../OpenGL/Shader.h"


Game::Game()
	: m_window(Window(1280, 720, "MineClone", true)),
	m_world(World::get()),
	m_renderer(Renderer())
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

		m_world.update(dt);
		m_renderer.renderScene(m_world.getScene());

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
