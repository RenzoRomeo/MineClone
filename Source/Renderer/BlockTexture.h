#pragma once

#include "../core.h"
#include "../World/Block.h"

namespace BlockTexture
{
	glm::ivec2 getBlockAtlas(const Block& block, const glm::ivec3& direction);
}