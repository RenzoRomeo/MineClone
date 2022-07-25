#include "Chunk.h"

#include "../Renderer/ChunkMeshGenerator.h"

Chunk::Chunk(const glm::ivec2 position)
    : m_position(position), m_hasUpdated(true)
{

}

Chunk::Chunk(const glm::ivec2 position, std::shared_ptr<std::array<std::array<std::array<Block, horizontalSize>, verticalSize>, horizontalSize>> blocks)
    : m_position(position), m_blocks(blocks), m_hasUpdated(true)
{
}

Chunk::~Chunk()
{
}

void Chunk::update(float dt)
{
    if (m_hasUpdated)
    {
        m_mesh = ChunkMeshGenerator::generateMesh(this);
        m_hasUpdated = false;
    }
}

const Block& Chunk::getBlock(uint32_t x, uint32_t y, uint32_t z) const
{
    return m_blocks->at(x).at(y).at(z);
}

void Chunk::removeBlock(uint32_t x, uint32_t y, uint32_t z)
{
    m_blocks->at(x).at(y).at(z) = Block(BlockType::Air, false);
}
