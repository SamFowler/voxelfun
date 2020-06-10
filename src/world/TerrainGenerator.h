#pragma once

#include "../pch/pch_std.h"

#include "Sector.h"


class OpenSimplexNoise;

class TerrainGenerator
{
public:
    TerrainGenerator(int seed);

    void generateBlock(Block& block, const WorldPos& block_origin);
    void generateSector(Sector* sector, const SectorPos& sector_pos);
private:

    int m_seed;
};

