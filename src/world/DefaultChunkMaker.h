#pragma once

#include "../pch/pch_std.h"
//#include <vector>

class Voxel;
class Colour;

enum ChunkMakeType
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

namespace DefaultChunkMaker
{

    int indexFromXYZ(const unsigned& x, const unsigned& y, const unsigned& z, const unsigned& chunk_size);

    void makeChunk(const ChunkMakeType& type, std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeEmptyChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeGrassChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeRevealEarthChunk  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeDirtChunk  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeTreeChunk  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeRandomChunk(std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeDebugChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
    void makeLightChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size);
}
