#pragma once

#include "../pch/pch_std.h"
#include "Block.h"
#include "BlockColumnInfo.h"
#include "DefaultBlockMaker.h"
#include "SectorColours.h"

#include "../scenegraph/BlockTree.h"

class SectorManager;
class Uniforms;

class Sector
{
private:
    std::unordered_map<BlockPos, std::unique_ptr<Block>, PositionHash> m_blocks; //16*8*16 [x,y,z]
    std::array<BlockColumnInfo, 256> m_block_column_details; //16*16 - each entry represents 1 column of voxels

    BlockTree m_block_tree = { {SECTOR_WIDTH/2, SECTOR_HEIGHT/2, SECTOR_WIDTH/2}, {SECTOR_WIDTH/2, SECTOR_HEIGHT/2, SECTOR_WIDTH/2} };

    std::queue<BlockPos> blocks_to_mesh;
public:
    SectorColours colours;

public:
    Block*  addBlock(const BlockPos& position, const BlockMakeType&);
    Block*  addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels);

    Block* getBlock(const BlockPos& block_pos);

    void makeMeshes(const SectorManager* sector_manager, const SectorPos& sector_pos);

    void draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws);

private:
    uint32_t getIndex      (const BlockPos& block_pos);
    uint32_t getColumnIndex(const BlockPos& block_pos);
};