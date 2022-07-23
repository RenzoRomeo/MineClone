#pragma once

#include "../core.h"

#include "Chunk.h"

namespace ChunkGenerator
{
	std::shared_ptr<Chunk> generateChunk(glm::ivec2 position)
	{
		std::array<Block, Chunk::totalBlocks> blocks;
		for (size_t y = 0; y < Chunk::verticalSize; y++)
		{
			for (size_t x = 0; x < Chunk::horizontalSize; x++)
			{
				for (size_t z = 0; z < Chunk::horizontalSize; z++)
				{
					blocks.at(Chunk::index(x, y, z)) = { BlockType::Dirt, true };
				}
			}
		}
		return std::make_shared<Chunk>(position, blocks);
	}
};