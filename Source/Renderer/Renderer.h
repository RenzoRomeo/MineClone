#pragma once

#include "../OpenGL/Shader.h"
#include "../OpenGL/Texture.h"
#include "Scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void renderScene(Scene scene);

private:
	Shader m_shader;
	Texture m_atlas;
};