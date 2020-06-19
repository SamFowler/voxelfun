#pragma once

#include "../pch/pch_std.h"
#include "Block.h"
#include "BlockColumnInfo.h"
#include "DefaultBlockMaker.h"
#include "SectorColours.h"

#include "../scenegraph/BlockTree.h"

class Uniforms;

class Sector
{
private:
    std::array<std::unique_ptr<Block>, SECTOR_WIDTH*SECTOR_WIDTH*SECTOR_WIDTH> m_blocks; //16*8*16 [x,y,z]
    std::array<BlockColumnInfo, 256> m_block_column_details; //16*16 - each entry represents 1 column of voxels

    BlockTree m_block_tree = { {SECTOR_WIDTH/2, SECTOR_HEIGHT/2, SECTOR_WIDTH/2}, {SECTOR_WIDTH/2, SECTOR_HEIGHT/2, SECTOR_WIDTH/2} };

    std::queue<BlockPos> blocks_to_mesh;
public:
    SectorColours colours;

public:
    Block*  addBlock(const BlockPos& position, const BlockMakeType&);
    Block*  addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels);
    void updateBlockNeighbours(const BlockPos& block_pos);

    Block* getBlock(const BlockPos& block_pos);

    void makeMeshes();

    void draw(const Uniforms& uniforms);

private:
    uint32_t getIndex      (const BlockPos& block_pos);
    uint32_t getColumnIndex(const BlockPos& block_pos);
};