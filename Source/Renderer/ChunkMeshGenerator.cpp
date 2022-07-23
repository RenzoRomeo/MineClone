#include "ChunkMeshGenerator.h"

#include "../World/Chunk.h"
#include "BlockMeshGenerator.h"

const glm::ivec3 sides[] = {
	{1, 0, 0},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0},
	{0, 0, 1},
	{0, 0, -1}
};

Mesh ChunkMeshGenerator::generateMesh(std::shared_ptr<const Chunk> chunk)
{
	std::vector<BlockVertex> vertices;
	for (size_t y = 0; y < Chunk::verticalSize; y++)
	{
		for (size_t x = 0; x < Chunk::horizontalSize; x++)
		{
			for (size_t z = 0; z < Chunk::horizontalSize; z++)
			{
				const Block& block = chunk->getBlock(x, y, z);
				for (size_t i = 0; i < 6; i++)
				{
					std::vector<BlockVertex> faceVertices = BlockMeshGenerator::generateMesh(block, sides[i]);
					for (auto& v : faceVertices)
					{
						v.position.x += x;
						v.position.y += y;
						v.position.z += z;
					}
					vertices.insert(vertices.end(), faceVertices.begin(), faceVertices.end());
				}
			}
		}
	}

	std::shared_ptr<Vao> vao = std::make_shared<Vao>();
	vao->bind();

	Vbo vbo(vertices.data(), vertices.size() * sizeof(BlockVertex));
	vbo.bind();

	VboLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(2);
	vao->addBuffer(vbo, layout);

	return Mesh(vao, vertices.size());
}
