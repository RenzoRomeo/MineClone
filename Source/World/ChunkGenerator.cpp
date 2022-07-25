#include "ChunkGenerator.h"

#include "Chunk.h"
#include "World.h"

namespace ChunkGenerator
{
	namespace
	{
		float map(float value, float inA, float inB, float outA, float outB)
		{
			float slope = 1.0f * (outB - outA) / (inB - inA);
			return outA + slope * (value - inA);
		}
	}

	std::shared_ptr<Chunk> ChunkGenerator::generateChunk(glm::ivec2 position)
	{
		auto blocks = std::make_shared<std::array<std::array<std::array<Block, Chunk::horizontalSize>, Chunk::verticalSize>, Chunk::horizontalSize>>();
		for (size_t x = 0; x < Chunk::horizontalSize; x++)
		{
			for (size_t z = 0; z < Chunk::horizontalSize; z++)
			{
				glm::vec2 absoluteBlockPosition{ ((float)position.x + x), ((float)position.y + z) };
				absoluteBlockPosition.x = map(absoluteBlockPosition.x, 0.0f, (float)(World::worldSize * Chunk::horizontalSize), -1.0f, 1.0f);
				absoluteBlockPosition.y = map(absoluteBlockPosition.y, 0.0f, (float)(World::worldSize * Chunk::horizontalSize), -1.0f, 1.0f);
				float noise = glm::simplex(absoluteBlockPosition);
				float height = map(noise, -1.0f, 1.0f, 0.0f, (float)Chunk::verticalSize);
				for (size_t y = 0; y < Chunk::verticalSize; y++)
				{
					if (y > height)
						blocks->at(x).at(y).at(z) = Block{ BlockType::Air, false };
					else
						blocks->at(x).at(y).at(z) = Block{ BlockType::Wood, true };
				}
			}
		}
		return std::make_shared<Chunk>(position, blocks);
	}
}