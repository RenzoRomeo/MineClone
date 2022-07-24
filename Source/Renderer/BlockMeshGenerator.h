#pragma once

#include "../core.h"

#include "../World/Block.h"

struct BlockVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec2 atlasCoords;
};

enum Sides
{
	YP,
	YN,
	XP,
	XN,
	ZP,
	ZN
};

namespace BlockMeshGenerator
{
	std::vector<BlockVertex> generateMesh(const Block& block, Sides side);
}