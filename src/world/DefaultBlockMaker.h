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

    int indexFromXYZ(const unsigned& x, const unsigned& y, const unsigned& z, const unsigned& block_size);

    void makeBlock(const BlockMakeType& type, std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeEmptyBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeGrassBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeRevealEarthBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeDirtBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeTreeBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeRandomBlock(std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeDebugBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
    void makeLightBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size);
}
