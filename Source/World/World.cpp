#include "World.h"

#include "ChunkGenerator.h"
#include "Chunk.h"
#include "../Renderer/ChunkMeshGenerator.h"

World::World()
	: m_player(Player({ 0, 6, 0 }))
{
	for (int x = 0; x < worldSize; x++)
	{
		for (int z = 0; z < worldSize; z++)
		{
			glm::ivec2 chunkPos{ x, z };
			m_chunks[chunkPos] = ChunkGenerator::generateChunk(chunkPos);
		}
	}
	// m_chunks[glm::ivec2{ 0, 0 }] = ChunkGenerator::generateChunk(glm::ivec2{ 0, 0 });
	// m_chunks[glm::ivec2{ 1, 0 }] = ChunkGenerator::generateChunk(glm::ivec2{ 1, 0 });
	// m_chunks[glm::ivec2{ 2, 0 }] = ChunkGenerator::generateChunk(glm::ivec2{ 2, 0 });
	// m_chunks[glm::ivec2{ 1, 1 }] = ChunkGenerator::generateChunk(glm::ivec2{ 1, 1 });
}

World& World::get()
{
	static World s_world{};
	return s_world;
}

void World::update(float dt)
{
	for (auto& [chunkPos, chunk] : m_chunks)
	{
		chunk->update(dt);
	}
	m_player.update(dt);
}

std::shared_ptr<Chunk> World::getChunk(const glm::ivec2& position)
{
	if (m_chunks.contains(position))
	{
		return m_chunks[position];
	}
	return nullptr;
}

std::shared_ptr<Chunk> World::getChunk(const glm::vec3& position)
{
	glm::ivec2 chunkPosition{ (int32_t)position.x / Chunk::horizontalSize, (int32_t)position.z / Chunk::horizontalSize };
	if (m_chunks.contains(chunkPosition))
	{
		return m_chunks[chunkPosition];
	}
	return nullptr;
}

Scene World::getScene() const
{
	Scene scene;

	glm::vec3 cameraPos = m_player.getCamera().position;
	glm::vec3 cameraFront = m_player.getCamera().front;
	glm::vec3 cameraUp = m_player.getCamera().up;
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 projection = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 10000.0f);

	scene.view = view;
	scene.projection = projection;

	for (const auto& [chunkPos, chunk] : m_chunks)
	{
		glm::vec3 scale{ 1.0f };
		glm::vec3 position{ (float)chunkPos.x * Chunk::horizontalSize, 0.0f, (float)chunkPos.y * Chunk::horizontalSize };
		Transform t{scale, position};
		RenderObject ro{ ChunkMeshGenerator::generateMesh(chunk), t };
		scene.renderObjects.push_back(ro);
	}

	return scene;
}
