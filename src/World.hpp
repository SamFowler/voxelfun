#pragma once

#include "BChunk.hpp"
#include "Input.hpp"
#include "BlockManager.hpp"


#include <vector>
#include <memory>

class World
{
public:
    World(const int& block_size = 8) : m_block_manager(8) {};
    void init();
    void update(const Input &input);

    void addChunk(const BChunk& chunk) {
        // m_chunks.push_back(chunk);
        m_chunk_ptrs.push_back(std::make_unique<BChunk>(chunk));
        };

    std::vector<BlockRenderList*> getWorldRenderList();

private:

    std::vector<BChunk> m_chunks;

    std::vector<std::unique_ptr<BChunk>> m_chunk_ptrs;

    //std::vector<BlockRenderList> world_render_list;

    BlockManager m_block_manager;

};