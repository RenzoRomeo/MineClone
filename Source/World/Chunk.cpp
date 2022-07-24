#include "Chunk.h"

Chunk::Chunk(const glm::ivec2 position)
    : m_position(position), m_hasUpdated(false)
{

}

Chunk::Chunk(const glm::ivec2 position, std::array<std::array<std::array<Block, horizontalSize>, verticalSize>, horizontalSize> blocks)
    : m_position(position), m_blocks(blocks), m_hasUpdated(false)
{
}

Chunk::~Chunk()
{
}

void Chunk::update(float dt)
{
    
}

const Block& Chunk::getBlock(uint32_t x, uint32_t y, uint32_t z) const
{
    return m_blocks.at(x).at(y).at(z);
}

void Chunk::removeBlock(uint32_t x, uint32_t y, uint32_t z)
{
    m_blocks.at(x).at(y).at(z) = Block(BlockType::Air, false);
}
