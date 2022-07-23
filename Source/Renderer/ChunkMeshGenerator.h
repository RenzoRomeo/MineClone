#pragma once

#include "Mesh.h"

class Chunk;

namespace ChunkMeshGenerator
{
	Mesh generateMesh(std::shared_ptr<const Chunk> chunk);
}