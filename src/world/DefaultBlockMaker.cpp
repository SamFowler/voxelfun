#include "DefaultBlockMaker.h"

#include "Block.h"
#include "Voxel.h"
#include "Colour.h"
#include "Block.h"

namespace DefaultBlockMaker
{
    int indexFromXYZ(const unsigned& x, const unsigned& y, const unsigned& z, const unsigned& block_size)
    {
        return (y*block_size*block_size) + (z * block_size) + x;

    }

    void makeBlock(const BlockMakeType& type, std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        if (type == GRASS_CHUNK)
            makeGrassBlock(voxels, colours, block_size);
        else if (type == EMPTY_CHUNK)
            makeEmptyBlock(voxels, colours,block_size);
        else if (type == REVEAL_DIRT_CHUNK)
            makeRevealEarthBlock(voxels, colours, block_size);
        else if (type == DIRT_CHUNK)
            makeDirtBlock(voxels, colours,block_size);
        else if (type == TREE_CHUNK)
            makeTreeBlock(voxels, colours,block_size);
        else if (type == RANDOM_CHUNK)
            makeRandomBlock(voxels, colours,block_size);
        else if (type == LIGHT_CHUNK)
            makeLightBlock(voxels, colours, block_size);
        else
            makeDebugBlock(voxels, colours,block_size);
        

    }

    void makeEmptyBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {

        Voxel voxel = {0, VoxelType::Empty};
        voxels = std::move(std::vector<Voxel>(block_size*block_size*block_size, voxel));
        colours = { {0,0,0,0}};

    }

    void makeGrassBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        Voxel voxel_dirt = {1, VoxelType::Dirt};
        Voxel voxel_grass = {2, VoxelType::Grass};
        Voxel voxel_grass2 = {3, VoxelType::Grass};
        std::vector<Voxel> these_voxels(block_size*block_size*block_size, voxel_dirt);



        //int y = block_size-1;
        for (unsigned y = 0; y < block_size; y++)
        {
            for (unsigned z = 0; z < block_size; z++) 
            {
                for (unsigned x = 0; x < block_size; x++)
                {
                    if (y > block_size-3)
                    {
                        int index = indexFromXYZ(x,y,z, block_size);
                        these_voxels[index] = voxel_grass;
                        if ( (rand() % 10) == 0)
                        {
                            these_voxels[index] = voxel_grass2;
                        }
                    }
                }
            }
        }

        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {150, 100, 100, 255}, {0, 200, 0, 255}, {0, 170, 0, 255}};
    }
 
    void makeRevealEarthBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        Voxel voxel = {1, VoxelType::Dirt};
        Voxel voxel2 = {2, VoxelType::Dirt};
        Voxel empty_vox = {0, VoxelType::Empty};
        std::vector<Voxel> these_voxels(block_size*block_size*block_size, voxel);
        /* int y = block_size-1;

        for (unsigned z = 0; z < block_size; z++) 
        {
            for (unsigned x = 0; x < block_size; x++)
            {
                int index = indexFromXYZ(x,y,z, block_size);
                
                    these_voxels[index] = empty_vox;
                
                
            }
        } */

        int y = block_size-1;

        for (unsigned z = 0; z < block_size; z++) 
        {
            for (unsigned x = 0; x < block_size; x++)
            {
                int index = indexFromXYZ(x,y,z, block_size);
                if ( (rand() % 15) == 0)
                {
                    these_voxels[index] = voxel2;
                }
                else 
                {
                    these_voxels[index] = empty_vox;
                }
                
            }
        }

        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {150, 100, 100, 255}, {120, 80, 80, 255}};
    }

    void makeDirtBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        Voxel voxel = {1, VoxelType::Dirt};
        Voxel voxel2 = {2, VoxelType::Dirt};
        std::vector<Voxel> these_voxels(block_size*block_size*block_size, voxel);
        int y = block_size-1;

        for (unsigned z = 0; z < block_size; z++) 
        {
            for (unsigned x = 0; x < block_size; x++)
            {
                if ( (rand() % 15) == 0)
                {
                    int index = indexFromXYZ(x,y,z, block_size);
                    these_voxels[index] = voxel2;
                }
                
            }
        }

        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {150, 100, 100, 255}, {120, 80, 80, 255}};
    }

    void makeTreeBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        Voxel tree_bark = {1, VoxelType::Tree};
        Voxel tree_inside = {2, VoxelType::Tree};
        std::vector<Voxel> block_voxels(block_size*block_size*block_size, tree_bark);
        unsigned offset = block_size/8;
        unsigned sz_minus_off = (block_size - 1) - offset;
        unsigned mid_lower_bound = sz_minus_off - (block_size/2);
        unsigned mid_upper_bound = offset + (block_size/2);
        for (unsigned y = 0; y < block_size; y++)
        {
            for (unsigned z = 0; z < block_size; z++) 
            {
                for (unsigned x = 0; x < block_size; x++)
                {
                    if (
                        ( (x == offset || x == sz_minus_off) && (z >= offset && z <= sz_minus_off ) ) ||
                        ( (z == offset || z == sz_minus_off) && (x >= offset && x <= sz_minus_off ) ) ||
                        ( x > mid_lower_bound && z > mid_lower_bound && x < mid_upper_bound && z < mid_upper_bound )
                       )
                    {
                        int index = indexFromXYZ(x,y,z, block_size);
                        block_voxels[index] = tree_inside;
                    }
                }
            }
        }

        voxels = std::move(block_voxels);
        colours = { {0,0,0,0}, {110, 88, 82, 255}, {90, 70, 65, 255}};

    }

    void makeRandomBlock(std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        int num_colours = rand()%7+1;

        std::vector<Voxel> potential_voxels(num_colours); 
        potential_voxels[0] = {0, VoxelType::Empty};
        colours.push_back( {0,0,0,0} );
        for (int i = 1; i < num_colours; i++)
        {
            potential_voxels[i] = { (ColourID)(rand()%num_colours), VoxelType::Debug};
            colours.push_back({rand()%256, rand()%256, rand()%256, 255});
        }

        std::vector<Voxel> these_voxels(block_size*block_size*block_size);

        for (unsigned j = 0; j < block_size*block_size*block_size; j++)
        {
            these_voxels[j] = potential_voxels[rand() % num_colours];

        }

        voxels = std::move(these_voxels);



    }

    void makeDebugBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {
        std::vector<Voxel> these_voxels(block_size*block_size*block_size, {1, VoxelType::Debug});
        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {255, 0, 255, 255} };
    }

    void makeLightBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours, const unsigned int& block_size)
    {

        std::vector<Voxel> these_voxels(block_size*block_size*block_size, {1, VoxelType::LightSrc});
        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {255, 236, 178, 255} };
    }


}