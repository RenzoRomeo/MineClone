#include "BlockTexture.h"

glm::ivec2 BlockTexture::getBlockAtlas(const Block& block, const glm::ivec3& direction)
{
    if (block.type == BlockType::Dirt)
    {
        if (direction.y == 1) return { 0, 0 };
        if (direction.y == -1) return { 2, 0 };
        return { 1, 0 };
    }

    if (block.type == BlockType::Wood)
    {
        if (direction.y == 1) return { 3, 1 };
        if (direction.y == -1) return { 3, 1 };
        return { 2, 1 };
    }
}
