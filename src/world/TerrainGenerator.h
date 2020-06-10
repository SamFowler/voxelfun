#pragma once

#include "../pch/pch_std.h"

#include "Sector.h"


class OpenSimplexNoise;

class TerrainGenerator
{
public:
    TerrainGenerator(int seed);

    void generateBlock(Block& block, const WorldPos& block_origin);

    double getNoise(OpenSimplexNoise& simplex_gen, const glm::vec2& pos);
    double getNoise(OpenSimplexNoise& simplex_gen, const glm::vec3& pos);

    std::vector<std::pair<const BlockPos, Block &>> generateSector(Sector* sector, const SectorPos& sector_pos);
private:

    int m_seed;
};

