#pragma once

#include "../core.h"

#include "RenderObject.h"

struct Scene
{
	std::vector<RenderObject> renderObjects;
	glm::mat4 view;
	glm::mat4 projection;
};