#pragma once

#include "Scene.h"

struct RendererConfig
{
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	const char* atlasSource;
};

namespace Renderer
{
	void init(RendererConfig config);
	void renderScene(Scene scene);
	void clean();
}