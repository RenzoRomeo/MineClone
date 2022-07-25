#pragma once

#include "Mesh.h"

class Chunk;

namespace ChunkMeshGenerator
{
	Mesh generateMesh(Chunk* chunk);
}