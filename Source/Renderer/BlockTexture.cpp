#include "BlockTexture.h"

namespace BlockTexture
{
	glm::ivec2 getBlockAtlas(const Block& block, Sides side)
	{
		if (block.type == BlockType::Grass)
		{
			if (side == Sides::YP) return { 0, 0 };
			if (side == Sides::YN) return { 2, 0 };
			return { 1, 0 };
		}

		if (block.type == BlockType::Dirt)
		{
			return { 2, 0 };
		}

		if (block.type == BlockType::Wood)
		{
			if (side == Sides::YP) return { 3, 1 };
			if (side == Sides::YN) return { 3, 1 };
			return { 2, 1 };
		}

		if (block.type == BlockType::Planks)
		{
			return { 6, 1 };
		}

		if (block.type == BlockType::Stone)
		{
			return { 3, 0 };
		}
	}
}
