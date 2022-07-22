#include "Game.h"

#include "Input.h"
#include "../OpenGL/Vbo.h"
#include "../OpenGL/Vao.h"
#include "../OpenGL/Ebo.h"
#include "../OpenGL/VboLayout.h"
#include "../OpenGL/Shader.h"

// Just a test
float vertices[] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f
};

uint32_t indices[] = {
	0, 1, 2,
	2, 3, 0
};

Game::Game()
	: m_window(Window(1280, 720, "MineClone", true))
{
}

void Game::run()
{
	Shader shader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");

	Vao vao;
	vao.bind();

	Vbo vbo(vertices, sizeof(vertices));

	VboLayout layout;
	layout.push<float>(2);
	vao.addBuffer(vbo, layout);

	Ebo ebo(indices, 6);

	float beginTime = glfwGetTime();
	float endTime;
	float dt = 0.016f;
	while (!m_window.shouldClose())
	{
		m_window.pollEvents();
		m_window.clear();

		shader.use();
		vao.bind();
		ebo.bind();
		glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);

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
