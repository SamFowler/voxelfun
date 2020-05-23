#pragma once

#include <vector>
#include <unordered_set>
#include <glm/vec3.hpp>

#include "BlockManager.hpp"
#include "BlockMeshGenerator.hpp"
#include "BlockMeshManager.hpp"

class BChunk
{
public:
    BChunk(const unsigned int& size, const glm::ivec3& position, const std::vector<BlockID>& blocks)
    : m_size(size), m_position(position), m_blocks(blocks), m_unique_blocks(m_blocks.begin(), m_blocks.end())
    {
    };

    int getSize() const { return m_size; }
    int getVolume() const { return m_size*m_size*m_size; }
    glm::ivec3 getChunkPosition() const { return m_position; }

    Mesh makeMesh(const BlockManager& block_manager) const;


private:
    int m_size;

    glm::ivec3 m_position;
    std::vector<BlockID> m_blocks;
    std::unordered_set<BlockID> m_unique_blocks;
};