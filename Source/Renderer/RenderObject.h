#pragma once

#include "../core.h"

#include "Mesh.h"

struct Transform
{
	glm::vec3 scale;
	glm::vec3 position;

	glm::mat4 getModel() const;
};

struct RenderObject
{
	Mesh mesh;
	Transform transform;
};