#include "BChunk.hpp"

#include <map>
#include <iostream>
#include <valarray>

#include "ChunkMeshGenerator.hpp"

BlockRenderList BChunk::getBlockRenderList() 
{
    if (m_render_list_needs_updating)
        updateBlockRenderList();

    return m_block_render_list;
}

BlockRenderList* BChunk::getBlockRenderListPtr() 
{
    if (m_render_list_needs_updating)
        updateBlockRenderList();

    return &m_block_render_list;
}


void BChunk::updateBlockRenderList()
{
    BlockRenderList render_list;

    glm::ivec3 chunk_world_pos = m_position * m_size;

    for (int y = 0; y < m_size; y++) {
        for (int z = 0; z < m_size; z++) {
            for (int x = 0; x < m_size; x++) {
                int index = x + z*m_size + y*m_size*m_size;

                glm::ivec3 block_world_pos = chunk_world_pos + glm::ivec3(x,y,z);
                if (m_blocks[index] != 0)
                {
                    render_list[m_blocks[index]].push_back(block_world_pos);
                }
            }   
        }
    }

    m_block_render_list = render_list;

}