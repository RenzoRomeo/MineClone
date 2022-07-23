#pragma once

#include "../core.h"

#include "Player.h"
#include "../Renderer/Scene.h"

class Chunk;

class World
{
public:
	static constexpr int32_t worldSize = 1;

public:
	World();

	void update(float dt);

	// Chunk coordinates (ints)
	std::shared_ptr<Chunk> getChunk(const glm::ivec2& position);

	// Absolute world coordinates (floats)
	std::shared_ptr<Chunk> getChunk(const glm::vec3& position);

	Scene getScene() const;

private:
	Player m_player;
	std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>> m_chunks;
};