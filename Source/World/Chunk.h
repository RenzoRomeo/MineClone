#pragma once

#include "../core.h"

#include "Block.h"

class Chunk
{
public:
	static constexpr uint32_t horizontalSize = 5;
	static constexpr uint32_t verticalSize = 2;
	static constexpr uint32_t totalBlocks = horizontalSize * horizontalSize * verticalSize;

public:
	Chunk(const glm::ivec2 position);
	Chunk(const glm::ivec2 position, std::array<Block, totalBlocks> block);
	~Chunk();

	void update(float dt);

	// Coordinates are in local chunk space
	const Block& getBlock(uint32_t x, uint32_t y, uint32_t z) const;

	void removeBlock(uint32_t x, uint32_t y, uint32_t z);

	inline static uint32_t index(uint32_t x, uint32_t y, uint32_t z)
	{
		return y * verticalSize * horizontalSize + x * horizontalSize + z;
	}

private:
	glm::ivec2 m_position;
	std::array<Block, totalBlocks> m_blocks;
	bool m_hasUpdated;
};