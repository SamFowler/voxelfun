#pragma once

#include "../pch/pch_std.h"

#include "Sector.h"

class Input;

class SectorManager
{
public:
    SectorManager(unsigned int block_size);
    void loadWorld(/* std::string file_name */);
    void loadSector(const SectorPos& sector_pos);

    void editSectors(Input& input);

    void updateSectors(std::vector<std::pair<const BlockPos, const Block*>> blocks_to_remesh);
    void addSector(SectorPos& sector_pos);

private:
    std::unordered_map<SectorPos, std::unique_ptr<Sector>, PositionHash> m_sectors;
    unsigned int m_num_sectors = 0;

    unsigned int m_block_size;
};