#include "Renderer.h"

#include "../OpenGL/Shader.h"
#include "../OpenGL/Texture.h"

namespace Renderer
{
	namespace
	{
		std::unique_ptr<Shader> shader = nullptr;
		std::unique_ptr<Texture> atlas = nullptr;
	}

	void init(RendererConfig config)
	{
		shader = std::make_unique<Shader>(config.vertexShaderSource, config.fragmentShaderSource);
		atlas = std::make_unique<Texture>(config.atlasSource);

		atlas->bindToSlot(0);
		shader->setUniform1i("uTexture", 0);
		
		shader->setUniform1i("uAtlasW", atlas->getWidth());
		shader->setUniform1i("uAtlasH", atlas->getHeight());
		shader->setUniform1i("uAtlasSpriteSize", 16);
	}

	void renderScene(Scene scene)
	{
		shader->setUniformMat4("uView", scene.view);
		shader->setUniformMat4("uProjection", scene.projection);

		for (const auto& r : scene.renderObjects)
		{
			shader->use();
			shader->setUniformMat4("uModel", r.transform.getModel());
			r.mesh.vao->bind();
			glDrawArrays(GL_TRIANGLES, 0, r.mesh.numVertices);
		}
	}

	void clean()
	{
		shader.reset();
		atlas.reset();
	}
}
