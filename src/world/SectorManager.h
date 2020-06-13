#pragma once

#include "../pch/pch_std.h"

#include "Sector.h"

class Input;

class SectorManager
{
public:
    void loadWorld(/* std::string file_name */);
    void loadSector(const SectorPos& sector_pos);

    void editSectors(Input& input);

    Sector& getSector(const SectorPos& sector_pos);
    Block&  getBlock (const SectorPos& sector_pos, const BlockPos& block_pos);
    Voxel& getVoxel(const SectorPos& sector_pos, const BlockPos& block_pos, const VoxelPos& voxel_pos);

    void updateSectors(std::vector<std::pair<const BlockPos, const Block*>> blocks_to_remesh);
    Sector* addSector(const SectorPos& sector_pos);

private:
    std::unordered_map<SectorPos, std::unique_ptr<Sector>, PositionHash> m_sectors;
    unsigned int m_num_sectors = 0;

    std::vector<SectorPos> m_sectors_to_update;

};