#pragma once

#include <vector>
#include <map>
#include <unordered_set>
#include <glm/vec3.hpp>

#include "BlockManager.hpp"
#include "BlockMeshGenerator.hpp"
#include "BlockMeshManager.hpp"

/*
struct BlockRenderList
{
    glm::ivec3 chunk_position;
    std::map<BlockID, std::vector<glm::ivec3>> block_positions;
};
*/

using BlockRenderList = std::map<BlockID, std::vector<glm::ivec3>>;


class BChunk
{
public:
    BChunk(const unsigned int& size, const glm::ivec3& position, const std::vector<BlockID>& blocks)
    : m_size(size), m_render_list_needs_updating(true), m_position(position), m_blocks(blocks), m_unique_blocks(m_blocks.begin(), m_blocks.end())
    {
    };

    int getSize() const { return m_size; }
    int getVolume() const { return m_size*m_size*m_size; }
    glm::ivec3 getChunkPosition() const { return m_position; }

    BlockRenderList getBlockRenderList();
    BlockRenderList* getBlockRenderListPtr();

    void updateBlockRenderList();
    

private:
    int m_size;

    bool m_render_list_needs_updating;

    glm::ivec3 m_position;
    std::vector<BlockID> m_blocks;
    std::unordered_set<BlockID> m_unique_blocks;

    BlockRenderList m_block_render_list;

    
};