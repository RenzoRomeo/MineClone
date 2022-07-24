#pragma once

#include "../core.h"

class Chunk;

namespace ChunkGenerator
{
	std::shared_ptr<Chunk> generateChunk(glm::ivec2 position);
};