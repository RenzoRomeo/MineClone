#pragma once

#include "../core.h"
#include "../World/Block.h"
#include "BlockMeshGenerator.h"

namespace BlockTexture
{
	glm::ivec2 getBlockAtlas(const Block& block, Sides side);
}