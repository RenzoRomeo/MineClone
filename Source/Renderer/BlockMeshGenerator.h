#pragma once

#include "../core.h"

#include "../World/Block.h"

struct BlockVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec2 atlasCoords;
};

namespace BlockMeshGenerator
{
	std::vector<BlockVertex> generateMesh(const Block& block, const glm::ivec3& direction);
}