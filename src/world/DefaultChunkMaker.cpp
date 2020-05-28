#include "DefaultChunkMaker.h"

#include "Chunk.h"
#include "Voxel.h"
#include "Colour.h"
#include "Chunk.h"

namespace DefaultChunkMaker
{
    int indexFromXYZ(const unsigned& x, const unsigned& y, const unsigned& z, const unsigned& chunk_size)
    {
        return (y*chunk_size*chunk_size) + (z * chunk_size) + x;

    }

    void makeChunk(const ChunkMakeType& type, std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {
        if (type == GRASS_CHUNK)
            makeGrassChunk(voxels, colours, chunk_size);
        else if (type == EMPTY_CHUNK)
            makeEmptyChunk(voxels, colours,chunk_size);
        else if (type == DIRT_CHUNK)
            makeDirtChunk(voxels, colours,chunk_size);
        else if (type == TREE_CHUNK)
            makeTreeChunk(voxels, colours,chunk_size);
        else if (type == RANDOM_CHUNK)
            makeRandomChunk(voxels, colours,chunk_size);
        else
            makeDebugChunk(voxels, colours,chunk_size);
        

    }

    void makeEmptyChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {

        Voxel voxel = {0, VoxelType::Empty};
        voxels = std::move(std::vector<Voxel>(chunk_size*chunk_size*chunk_size, voxel));
        colours = { {0,0,0,0}};

    }

    void makeGrassChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {
        Voxel voxel = {1, VoxelType::Grass};
        Voxel voxel2 = {2, VoxelType::Grass};
        std::vector<Voxel> these_voxels(chunk_size*chunk_size*chunk_size, voxel);
        int y = chunk_size-1;

        for (unsigned z = 0; z < chunk_size; z++) 
        {
            for (unsigned x = 0; x < chunk_size; x++)
            {
                if ( (rand() % 10) == 0)
                {
                    int index = indexFromXYZ(x,y,z, chunk_size);
                    these_voxels[index] = voxel2;
                }
                
            }
        }

        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {0, 255, 0, 255}, {0, 170, 0, 255}};
    }

    void makeDirtChunk  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {
        Voxel voxel = {1, VoxelType::Dirt};
        voxels = std::move(std::vector<Voxel>(chunk_size*chunk_size*chunk_size, voxel));
        colours = { {0,0,0,0}, {150, 100, 100, 255}};
    }

    void makeTreeChunk  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {

    }

    void makeRandomChunk(std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {

    }

    void makeDebugChunk (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& chunk_size)
    {

    }

}