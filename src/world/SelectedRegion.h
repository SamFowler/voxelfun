#pragma once

#include "../pch/pch_std.h"

#include "Coordinates.h"

class Input;

class SelectedRegion
{
public:
    SelectedRegion() {};
    SelectedRegion(const SectorPos sector_pos, const BlockPos block_pos, const VoxelPos voxel_pos);

    void moveRegion(Input& input);

    WorldPos  getWorldPos();
    
    SectorPos getSectorPos();
    BlockPos  getBlockPos();
    VoxelPos  getVoxelPos();

    void printSelected();

private:

    SectorPos m_sector_pos = {0,0,0};
    BlockPos  m_block_pos  = {0,0,0};
    VoxelPos  m_voxel_pos  = {0,0,0};

    WorldPos m_world_pos = {0,0,0};

};