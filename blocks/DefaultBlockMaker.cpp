#include "DefaultBlockMaker.hpp"

namespace DefaultBlockMaker {

    Block makeBlock(const int& block_size, const DefaultBlockType& block_type) 
    {
        if (block_type == GRASS_ONE)
            return makeGrassOne(block_size);
        else if (block_type == GRASS_TWO)
            return makeGrassTwo(block_size);
        else if (block_type == DIRT_ONE)
            return makeDirtOne(block_size);
        else
            return makePlaceholder(block_size);
    }

    Block makeGrassOne(const int& block_size)
    {
         
        std::vector<VoxelID> voxels(block_size*block_size*block_size, 1);
    
        int y = block_size - 1;
        for (int z = 0; z < block_size; z++) {
            for (int x = 0; x < block_size; x++) {
                int voxel_index = x + z*block_size + y*block_size*block_size;
                if (rand() % 10 == 0)
                    voxels[voxel_index] = 2;
            }
        }

        std::vector<Colour> colours = {{0.36f, 0.70f, 0.38f, 1.0f}, {0.63f, 0.90f, 0.35, 1.0f}, {0.39f, 0.83f, 0.74f, 0.5f}};
        Block block(block_size, voxels, colours);
        block.makeNeighbours();
        return block;
    }
    
    Block makeGrassTwo(const int& block_size)
    {

        std::vector<VoxelID> voxels(block_size*block_size*block_size, 1);
    
        int y = block_size - 1;
        for (int z = 0; z < block_size; z++) {
            for (int x = 0; x < block_size; x++) {
                int voxel_index = x + z*block_size + y*block_size*block_size;
                if (rand() % 10 == 0)
                    voxels[voxel_index] = 2;
                else 
                    voxels[voxel_index] = 3;
            }
        }
        
        std::vector<Colour> colours = {{0.36f, 0.70f, 0.38f, 1.0f}, {0.976f, 0.57f, 0.32, 1.0f}, {0.39f, 0.83f, 0.74f, 0.5f}};
        Block block(block_size, voxels, colours);
        block.makeNeighbours();

        return block;
        
    }

    Block makeDirtOne(const int& block_size)
    {
        std::vector<VoxelID> voxels(block_size*block_size*block_size, 1);
        std::vector<Colour> colours = {{0.21f, 0.14f, 0.07f, 1.0f}};

        Block block(block_size, voxels, colours);
        block.makeNeighbours();

        return block;
    }

    Block makePlaceholder(const int& block_size)
    {
        std::vector<VoxelID> voxels(block_size*block_size*block_size, 1);
    
        std::vector<Colour> colours = {{1.0f, 0.0f, 1.0f, 1.0f}};
        Block block(block_size, voxels, colours);
        block.makeNeighbours();

        return block;
    }
}