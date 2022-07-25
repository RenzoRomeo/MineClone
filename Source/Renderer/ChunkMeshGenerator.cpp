#include "ChunkMeshGenerator.h"

#include "../World/World.h"
#include "../World/Chunk.h"
#include "BlockMeshGenerator.h"


namespace ChunkMeshGenerator
{
	namespace
	{
		bool isEdgeBlock(int x, int y, int z)
		{
			return x == 0 || x == Chunk::horizontalSize - 1 || z == 0 || z == Chunk::horizontalSize - 1 || y == 0 || y == Chunk::verticalSize - 1;
		}

		bool isEdgeFace(int x, int y, int z, Sides side)
		{
			if (!isEdgeBlock(x, y, z)) return false;

			if (x == 0 && side == Sides::XN) return true;
			if (x == Chunk::horizontalSize - 1 && side == Sides::XP) return true;
			if (y == 0 && side == Sides::YN) return true;
			if (y == Chunk::verticalSize - 1 && side == Sides::YP) return true;
			if (z == 0 && side == Sides::ZN) return true;
			if (z == Chunk::horizontalSize - 1 && side == Sides::ZP) return true;

			return true;
		}

		bool isBlockInsideChunk(int x, int y, int z)
		{
			return !(x < 0 || x >= Chunk::horizontalSize || z < 0 || z >= Chunk::horizontalSize || y < 0 || y >= Chunk::verticalSize);
		}

		bool isNeighborSolidOutside(Chunk* chunk, int x, int y, int z, Sides side)
		{
			return false;
			// Culling between chunks is disabled for now...
			// There can't be chunks on top of chunks, so no solid block will be on top of a chunk.
			if (side == Sides::YP || side == Sides::YN)
				return false;

			World& world = World::get();
			glm::ivec2 chunkPos = chunk->getPosition();

			int xOff = 0;
			int zOff = 0;
			if (side == Sides::XP) xOff = 1;
			else if (side == Sides::XN) xOff = -1;
			else if (side == Sides::ZP) zOff = 1;
			else if (side == Sides::ZN) zOff = -1;

			glm::ivec2 neighborCoords{ chunkPos.x + xOff, chunkPos.y + zOff };
			std::shared_ptr<const Chunk> neighbor = world.getChunk(neighborCoords);

			if (neighbor == nullptr) return false;

			if (side == Sides::XP) return neighbor->getBlock(0, y, z).solid;
			if (side == Sides::XN) return neighbor->getBlock((int)Chunk::horizontalSize - 1, y, z).solid;
			if (side == Sides::ZP) return neighbor->getBlock(x, y, 0).solid;
			if (side == Sides::ZN) return neighbor->getBlock(x, y, (int)Chunk::horizontalSize - 1).solid;

			return false;
		}

		bool isNeighborSolidInside(Chunk* chunk, int x, int y, int z, Sides side)
		{
			if (side == Sides::YP)
				if (!isBlockInsideChunk(x, y + 1, z))
					return false;
				else
					return chunk->getBlock(x, y + 1, z).solid;

			if (side == Sides::YN)
				if (!isBlockInsideChunk(x, y - 1, z))
					return false;
				else
					return chunk->getBlock(x, y - 1, z).solid;

			if (side == Sides::XP)
				if (!isBlockInsideChunk(x + 1, y, z))
					return false;
				else
					return chunk->getBlock(x + 1, y, z).solid;

			if (side == Sides::XN)
				if (!isBlockInsideChunk(x - 1, y, z))
					return false;
				else
					return chunk->getBlock(x - 1, y, z).solid;

			if (side == Sides::ZP)
				if (!isBlockInsideChunk(x, y, z + 1))
					return false;
				else
					return chunk->getBlock(x, y, z + 1).solid;

			if (side == Sides::ZN)
				if (!isBlockInsideChunk(x, y, z - 1))
					return false;
				else
					return chunk->getBlock(x, y, z - 1).solid;

			return false;
		}

		bool shouldRenderFace(Chunk* chunk, int x, int y, int z, Sides side)
		{
			return !isNeighborSolidInside(chunk, x, y, z, side) && !isNeighborSolidOutside(chunk, x, y, z, side);
		}
	}

	Mesh generateMesh(Chunk* chunk)
	{
		auto chunkVertices = std::make_shared<std::vector<BlockVertex>>();
		for (int y = 0; y < Chunk::verticalSize; y++)
		{
			for (int x = 0; x < Chunk::horizontalSize; x++)
			{
				for (int z = 0; z < Chunk::horizontalSize; z++)
				{
					const Block& block = chunk->getBlock(x, y, z);

					if (!block.solid) continue;

					std::vector<BlockVertex> blockVertices;

					if (shouldRenderFace(chunk, x, y, z, Sides::YP))
					{
						std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, Sides::YP);
						blockVertices.insert(blockVertices.end(), v.begin(), v.end());
					}

					if (shouldRenderFace(chunk, x, y, z, Sides::YN))
					{
						std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, Sides::YN);
						blockVertices.insert(blockVertices.end(), v.begin(), v.end());
					}

					if (shouldRenderFace(chunk, x, y, z, Sides::XP))
					{
						std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, Sides::XP);
						blockVertices.insert(blockVertices.end(), v.begin(), v.end());
					}

					if (shouldRenderFace(chunk, x, y, z, Sides::XN))
					{
						std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, Sides::XN);
						blockVertices.insert(blockVertices.end(), v.begin(), v.end());
					}

					if (shouldRenderFace(chunk, x, y, z, Sides::ZP))
					{
						std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, Sides::ZP);
						blockVertices.insert(blockVertices.end(), v.begin(), v.end());
					}

					if (shouldRenderFace(chunk, x, y, z, Sides::ZN))
					{
						std::vector<BlockVertex> v = BlockMeshGenerator::generateMesh(block, Sides::ZN);
						blockVertices.insert(blockVertices.end(), v.begin(), v.end());
					}

					for (auto& v : blockVertices)
					{
						v.position.x += (float)x;
						v.position.y += (float)y;
						v.position.z += (float)z;
					}

					chunkVertices->insert(chunkVertices->end(), blockVertices.begin(), blockVertices.end());
				}
			}
		}

		std::shared_ptr<Vao> vao = std::make_shared<Vao>();
		vao->bind();

		std::shared_ptr<Vbo> vbo = std::make_shared<Vbo>(chunkVertices->data(), chunkVertices->size() * sizeof(BlockVertex));
		vbo->bind();

		VboLayout layout;
		layout.push<float>(3);
		layout.push<float>(2);
		layout.push<float>(2);
		vao->addBuffer(vbo, layout);

		uint32_t nVert = chunkVertices->size();
		chunkVertices.reset();
		return Mesh{ vao, vbo, nVert };
	}
}