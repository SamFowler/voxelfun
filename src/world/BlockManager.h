/* #pragma once

//#include <unordered_map>
//#include <queue>
//#include <vector>
//#include <utility>

#include "../pch/pch_std.h"

#include "Block.h"

#include "../Input.h" // TODO: unsure if this should go here or not

#include "DefaultBlockMaker.h"

class BlockManager
{
public:
    friend class Block;

    // Constructors
    BlockManager(const size_t& block_size = 2) : m_block_size(block_size), 
                                             m_block_size_sq(block_size*block_size),
                                             m_block_volume(block_size*block_size*block_size)
                                             {};

    // Processors
    bool init();
    void update(const Input& input);
    void destroy();

    // Getters
    int getNumBlocks() const;
    
    void addBlock(const BlockPos& position, const BlockMakeType&);
    void addBlock(const BlockPos& position, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours);

    void replaceBlock(const Block&              block          );
    void addBlockToUpdateList(const BlockPos& block_pos);

    void clearUpdatedBlockList();
    std::vector<const Block*> getUpdatedBlockList() const;
    
    const Block* getBlockPtr(const BlockPos& block_pos) const; 

private:
    // Helpers
    bool blockExists (const BlockPos&           block_position ) const;
    bool removeBlock (const BlockPos&           block_position );

private:

    // Data
    std::unordered_map<BlockPos, Block, PositionHash> m_blocks;
    int m_num_blocks;

    //std::queue<> m_updated_block_list;
    std::vector<const Block*> m_updated_block_list;

    unsigned int m_block_size;
    unsigned int m_block_size_sq;
    unsigned int m_block_volume;

}; */