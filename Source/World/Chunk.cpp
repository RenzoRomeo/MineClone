#include "Chunk.h"

Chunk::Chunk(const glm::ivec2 position)
    : m_position(position), m_hasUpdated(false)
{

}

Chunk::Chunk(const glm::ivec2 position, std::array<Block, totalBlocks> blocks)
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
    return m_blocks.at(index(x, y, z));
}

void Chunk::removeBlock(uint32_t x, uint32_t y, uint32_t z)
{
    m_blocks.at(index(x, y, z)) = Block(BlockType::Air, false);
}
