#include "Renderer.h"

Renderer::Renderer()
	: m_shader(Shader("Resources\\Shaders\\default.vert", "Resources\\Shaders\\default.frag")),
	m_atlas(Texture("Resources\\Images\\blocks.png"))
{
	m_atlas.bindToSlot(0);
	m_shader.setUniform1i("uTexture", 0);

	m_shader.setUniform1i("uAtlasW", m_atlas.getWidth());
	m_shader.setUniform1i("uAtlasH", m_atlas.getHeight());
	m_shader.setUniform1i("uAtlasSpriteSize", 16);
}

Renderer::~Renderer()
{
}

void Renderer::renderScene(Scene scene)
{
	m_shader.setUniformMat4("uView", scene.view);
	m_shader.setUniformMat4("uProjection", scene.projection);

	for (const auto& r : scene.renderObjects)
	{
		m_shader.use();
		m_shader.setUniformMat4("uModel", r.transform.getModel());
		r.mesh.vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, r.mesh.numVertices);
	}
}
