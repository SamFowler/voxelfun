#pragma once

#include "../pch/pch_std.h"

#include "Sector.h"
#include "TerrainGenerator.h"

class Input;
class Uniforms;

class SectorManager
{
public:
    SectorManager() : m_terrain_generator(WORLD_SEED) {};

    void loadWorld(/* std::string file_name */);
    void loadSector(const SectorPos& sector_pos);

    void editSectors(Input& input);

    Sector* addSector(const SectorPos& sector_pos);
    Sector* getSector(const SectorPos& sector_pos);
    Sector* createSector(const SectorPos& sector_pos);

    Block* getBlock (const SectorPos& sector_pos, const BlockPos& block_pos);
    Voxel& getVoxel(const SectorPos& sector_pos, const BlockPos& block_pos, const VoxelPos& voxel_pos);

    void generateWorld(const SectorPos& sector_pos, const BlockPos& block_pos);

    void update();
    void draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws);

private:
    std::unordered_map<SectorPos, std::unique_ptr<Sector>, PositionHash> m_sectors;
    unsigned int m_num_sectors = 0;

    std::vector<SectorPos> m_sectors_to_update;

    TerrainGenerator m_terrain_generator;


};