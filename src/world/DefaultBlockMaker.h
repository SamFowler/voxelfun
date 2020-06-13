#pragma once

#include "../pch/pch_std.h"

class Voxel;
class Colour;

enum BlockMakeType
{
    EMPTY_CHUNK = 0,
    GRASS_CHUNK,
    DIRT_CHUNK,
    TREE_CHUNK,
    LIGHT_CHUNK,
    RANDOM_CHUNK,
    REVEAL_DIRT_CHUNK,
    DEBUG_CHUNK
};

namespace DefaultBlockMaker
{

    int indexFromXYZ(const unsigned& x, const unsigned& y, const unsigned& z);

    void makeBlock(const BlockMakeType& type, std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeEmptyBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeGrassBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeRevealEarthBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeDirtBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeTreeBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeRandomBlock(std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeDebugBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
    void makeLightBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours);
}
