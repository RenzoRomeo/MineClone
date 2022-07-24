#include "ChunkGenerator.h"

#include "Chunk.h"

namespace ChunkGenerator
{
    std::shared_ptr<Chunk> ChunkGenerator::generateChunk(glm::ivec2 position)
	{
		std::array<std::array<std::array<Block, Chunk::horizontalSize>, Chunk::verticalSize>, Chunk::horizontalSize> blocks;
		for (size_t y = 0; y < Chunk::verticalSize; y++)
		{
			for (size_t x = 0; x < Chunk::horizontalSize; x++)
			{
				for (size_t z = 0; z < Chunk::horizontalSize; z++)
				{
					blocks.at(x).at(y).at(z) = Block{BlockType::Wood, true};
				}
			}
		}
		return std::make_shared<Chunk>(position, blocks);
	}
}