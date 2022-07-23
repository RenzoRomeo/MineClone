#include "Game.h"

#include "Window.h"
#include "Input.h"
#include "Logging.h"

#include "../World/World.h"

#include "../Renderer/Renderer.h"
#include "../OpenGL/Vbo.h"
#include "../OpenGL/Vao.h"
#include "../OpenGL/Ebo.h"
#include "../OpenGL/VboLayout.h"
#include "../OpenGL/Shader.h"

namespace MineClone
{
	namespace
	{
		std::unique_ptr<Window> window = nullptr;
		bool initialized = false;
	}

	void init(GameConfig config)
	{
		window = std::make_unique<Window>(config.windowWidth, config.windowHeight, config.title, config.vSync);

		RendererConfig rendererConfig;
		rendererConfig.vertexShaderSource = "Resources\\Shaders\\default.vert";
		rendererConfig.fragmentShaderSource = "Resources\\Shaders\\default.frag";
		rendererConfig.atlasSource = "Resources\\Images\\blocks.png";

		Renderer::init(rendererConfig);

		initialized = true;
	}

	void run()
	{
		World& world = World::get();

		if (!initialized)
		{
			LOG(LogType::ERROR, "Game has not been initialized.");
			exit(EXIT_FAILURE);
		}

		float beginTime = glfwGetTime();
		float endTime;
		float dt = 0.016f;
		while (!window->shouldClose())
		{
			window->pollEvents();
			window->clear();
		
			world.update(dt);
			Renderer::renderScene(world.getScene());
		
			window->swapBuffers();
			endTime = glfwGetTime();
			dt = endTime - beginTime;
			beginTime = endTime;
		
			if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
			{
				window->close();
			}
		}

		Renderer::clean();
	}
}