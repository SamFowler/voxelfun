#pragma once

#include "../pch/pch_std.h"

#include "Coordinates.h"

class Input;

class SelectedRegion
{
public:
    SelectedRegion() {};
    SelectedRegion(const SectorPos sector_pos, const BlockPos block_pos, const VoxelPos voxel_pos,
                    unsigned int m_block_size, unsigned int m_sector_height, unsigned int m_sector_size
    );

    void moveRegion(Input& input);
    void moveLeftRight(int amount);

    WorldPos getWorldPos();
    SectorPos getSectorPos();
    BlockPos getBlockPos();
    VoxelPos getVoxelPos();

    void printSelected();

private:

    SectorPos m_sector_pos = {0,0,0};
    BlockPos  m_block_pos  = {0,0,0};
    VoxelPos  m_voxel_pos  = {0,0,0};

    WorldPos m_world_pos = {0,0,0};

    int m_block_size;
    unsigned int m_sector_height;
    unsigned int m_sector_size;

    int m_sect_times_block_sizes;
    int m_sect_height_times_block_size;
};