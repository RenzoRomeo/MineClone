#pragma once

#include "../core.h"

#include "Block.h"

class Chunk
{
public:
	static constexpr uint32_t horizontalSize = 3;
	static constexpr uint32_t verticalSize = 2;

public:
	Chunk(const glm::ivec2 position);
	Chunk(const glm::ivec2 position, std::array<std::array<std::array<Block, horizontalSize>, verticalSize>, horizontalSize> blocks);
	~Chunk();

	void update(float dt);

	// Coordinates are in local chunk space
	const Block& getBlock(uint32_t x, uint32_t y, uint32_t z) const;

	void removeBlock(uint32_t x, uint32_t y, uint32_t z);

	inline glm::ivec2 getPosition() const { return m_position; }

private:
	glm::ivec2 m_position;
	std::array<std::array<std::array<Block, horizontalSize>, verticalSize>, horizontalSize> m_blocks;
	bool m_hasUpdated;
};