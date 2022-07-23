#include "ChunkMeshGenerator.h"

#include "../World/World.h"
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

enum Sides
{
	XP,
	XN,
	ZP,
	ZN,
	YP,
	YN
};

bool renderBorderFace(std::shared_ptr<const Chunk> chunk, int x, int y, int z, const glm::vec3& direction)
{
	World& world = World::get();
	glm::vec2 chunkPos = chunk->getPosition();

	std::shared_ptr<const Chunk> neighbor = world.getChunk(glm::ivec2{ chunkPos.x + direction.x, chunkPos.y + direction.z });

	if (neighbor == nullptr) return true;

	if (direction.x == 1.0f) return !neighbor->getBlock(0, y, z).solid;
	if (direction.x == -1.0f) return !neighbor->getBlock(Chunk::horizontalSize - 1, y, z).solid;
	if (direction.z == 1.0f) return !neighbor->getBlock(x, y, 0).solid;
	if (direction.z == -1.0f) return !neighbor->getBlock(x, y, Chunk::horizontalSize - 1).solid;

	return true;
}

Mesh ChunkMeshGenerator::generateMesh(std::shared_ptr<const Chunk> chunk)
{
	std::vector<BlockVertex> chunkVertices;
	for (int y = 0; y < Chunk::verticalSize; y++)
	{
		for (int x = 0; x < Chunk::horizontalSize; x++)
		{
			for (int z = 0; z < Chunk::horizontalSize; z++)
			{
				const Block& block = chunk->getBlock(x, y, z);

				if (!block.solid) continue;

				std::vector<BlockVertex> blockVertices;

				if (x == 0 && renderBorderFace(chunk, x, y, z, { -1, 0, 0 }))
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { -1, 0, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				} 
				else if (x == Chunk::horizontalSize - 1 && renderBorderFace(chunk, x, y, z, { 1, 0, 0 }))
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 1, 0, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}
				if (z == 0 && renderBorderFace(chunk, x, y, z, { 0, 0, -1 }))
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, 0, -1 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}
				else if (z == Chunk::horizontalSize - 1 && renderBorderFace(chunk, x, y, z, { 0, 0, 1 }))
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, 0, 1 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				// Faces on vertical extremes always render.
				if (y == 0)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, -1, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}
				else if (y == Chunk::verticalSize - 1)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, 1, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				// Check faces with other blocks inside this chunk
				if (x + 1 < Chunk::horizontalSize && !chunk->getBlock(x + 1, y, z).solid)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 1, 0, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				if (x - 1 >= 0 && !chunk->getBlock(x - 1, y, z).solid)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { -1, 0, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				if (z + 1 < Chunk::horizontalSize && !chunk->getBlock(x, y, z + 1).solid)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, 0, 1 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				if (z - 1 >= 0 && !chunk->getBlock(x, y, z - 1).solid)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, 0, -1 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				if (y + 1 < Chunk::verticalSize && !chunk->getBlock(x, y + 1, z).solid)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, 1, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				if (y - 1 >= 0 && !chunk->getBlock(x, y - 1, z).solid)
				{
					std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, { 0, -1, 0 });
					blockVertices.insert(blockVertices.end(), v.begin(), v.end());
				}

				for (auto& v : blockVertices)
				{
					v.position.x += x;
					v.position.y += y;
					v.position.z += z;
				}

				chunkVertices.insert(chunkVertices.end(), blockVertices.begin(), blockVertices.end());
			}
		}
	}

	std::shared_ptr<Vao> vao = std::make_shared<Vao>();
	vao->bind();

	Vbo vbo(chunkVertices.data(), chunkVertices.size() * sizeof(BlockVertex));
	vbo.bind();

	VboLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(2);
	vao->addBuffer(vbo, layout);

	return Mesh(vao, chunkVertices.size());
}
