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
public:

    std::pair<const BlockPos, Block&>  addBlock(const BlockPos& position, const BlockMakeType&);
    std::pair<const BlockPos, Block&>  addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels);
    void updateBlockNeighbours(const BlockPos& block_pos);

    //void addBlock(const BlockPos& block_pos, const BlockMakeType&);

    void editBlock(const BlockPos& block_pos /*, voxels/colours/changes */); //adds voxel edits to m_blocks_to_update to be changed once per frame
    void updateBlocks(std::vector<std::pair<const BlockPos, Block&>>& blocks_to_remesh); //updates blocks batched in m_blocks_to_update and add ptrs to them to remesh vector

    Block& getBlock(const BlockPos& block_pos);

    unsigned int getBlockIndexFromBlockPos(const BlockPos& block_pos);
    unsigned int getBlockColumnIndexFromBlockPos(const BlockPos& block_pos);

    void makeMeshes();

    SectorColours colours;

    void draw(const Uniforms& uniforms);

private:
    std::array<std::unique_ptr<Block>, SECTOR_WIDTH*SECTOR_WIDTH*SECTOR_WIDTH> m_blocks; //16*8*16 [x,y,z]
    std::array<BlockColumnInfo, 256> m_block_column_details; //16*16 - each entry represents 1 column of voxels

    std::vector<BlockPos> m_blocks_to_update;

    //std::unordered_map<ColourID, Colour> m_colours;

    BlockTree m_block_tree = { {SECTOR_WIDTH/2, SECTOR_HEIGHT/2, SECTOR_WIDTH/2}, {SECTOR_WIDTH/2, SECTOR_HEIGHT/2, SECTOR_WIDTH/2} };

    //std::vector<BlockPos> blocks_to_mesh;
    std::queue<BlockPos> blocks_to_mesh;

};