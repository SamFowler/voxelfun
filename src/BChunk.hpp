#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "BlockManager.hpp"
#include "BlockMeshGenerator.hpp"

class BChunk
{
public:
    BChunk(const unsigned int& size, const glm::ivec3& position, const std::vector<BlockID>& blocks)
    : m_size(size), m_size_sq(size * size), m_volume(size * size * size), 
    m_position(position), m_blocks(blocks)
    {
    };

    unsigned int getSize() const { return m_size; }
    unsigned int getVolume() const { return m_volume; }
    glm::ivec3 getChunkPosition() const { return m_position; }

    //ChunkMesh makeChunkMesh(const int& block_index, const MeshMethod& mesh_method = CULL_MESH_FAST) const;

private:
    unsigned int m_size;
    unsigned int m_size_sq;
    unsigned int m_volume;

    glm::ivec3 m_position;
    std::vector<BlockID> m_blocks;

    

};