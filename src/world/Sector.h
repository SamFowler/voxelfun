#pragma once

#include "../pch/pch_std.h"
#include "Block.h"
#include "BlockColumnInfo.h"
#include "DefaultBlockMaker.h"


class Sector
{
public:
    Sector(unsigned int block_size) : m_block_size(block_size) {};

    std::pair<const BlockPos, const Block*> addBlock(const BlockPos& position, const BlockMakeType&);
    std::pair<const BlockPos, const Block*> addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours);
    //void addBlock(const BlockPos& block_pos, const BlockMakeType&);

    void editBlock(const BlockPos& block_pos /*, voxels/colours/changes */); //adds voxel edits to m_blocks_to_update to be changed once per frame
    void updateBlocks(std::vector<std::pair<const BlockPos, const Block*>> blocks_to_remesh); //updates blocks batched in m_blocks_to_update and add ptrs to them to remesh vector

    unsigned int getBlockIndexFromBlockPos(const BlockPos& block_pos);
    unsigned int getBlockColumnIndexFromBlockPos(const BlockPos& block_pos);
private:
    std::array<Block, 2048> m_blocks; //16*8*16 [x,y,z]
    std::array<BlockColumnInfo, 256> m_block_column_details; //16*16 - each entry represents 1 column of voxels

    std::vector<BlockPos> m_blocks_to_update;

    unsigned int m_block_size = 32;

};