#include "World.h"

#include "ChunkGenerator.h"
#include "../Renderer/ChunkMeshGenerator.h"

World::World()
	: m_player(Player({0, 6, 0}))
{
	for (int32_t x = -worldSize; x < worldSize; x++)
	{
		for (int32_t z = -worldSize; z < worldSize; z++)
		{
			glm::vec2 chunkPos{ x, z };
			m_chunks[chunkPos] = ChunkGenerator::generateChunk(chunkPos);
		}
	}
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
		Transform t{ glm::vec3{1.0f}, glm::vec3{(float)chunkPos.x * Chunk::horizontalSize, 0.0f, (float)chunkPos.y * Chunk::horizontalSize}};
		RenderObject ro{ ChunkMeshGenerator::generateMesh(chunk), t };
		scene.renderObjects.push_back(ro);
	}

	return scene;
}
