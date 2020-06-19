#pragma once

#include "../pch/pch_std.h"

#include "Sector.h"

#include "../helpers/OpenSimplexNoise.h"

class OpenSimplexNoise;

class TerrainGenerator
{
public:
    TerrainGenerator(int seed);

    double getNoise(OpenSimplexNoise& simplex_gen, const glm::vec2& pos);
    double getNoise(OpenSimplexNoise& simplex_gen, const glm::vec3& pos);

    void addWorldColours(Sector& sector);
    void generateColumn(Sector& sector, const SectorPos& sector_pos, const BlockPos& block_pos);

private:

    OpenSimplexNoise m_simplex_generator;
    int m_seed;
};

