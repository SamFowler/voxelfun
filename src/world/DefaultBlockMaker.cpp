#include "DefaultBlockMaker.h"

#include "Block.h"
#include "Voxel.h"
#include "Colour.h"

#include "WorldConstants.h"

namespace DefaultBlockMaker
{
    int indexFromXYZ(const unsigned& x, const unsigned& y, const unsigned& z)
    {
        return (y*BLOCK_SIZE_SQ) + (z * BLOCK_SIZE) + x;

    }

    void makeBlock(const BlockMakeType& type, std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        if (type == GRASS_CHUNK)
            makeGrassBlock(voxels, colours);
        else if (type == EMPTY_CHUNK)
            makeEmptyBlock(voxels, colours);
        else if (type == REVEAL_DIRT_CHUNK)
            makeRevealEarthBlock(voxels, colours);
        else if (type == DIRT_CHUNK)
            makeDirtBlock(voxels, colours);
        else if (type == TREE_CHUNK)
            makeTreeBlock(voxels, colours);
        else if (type == RANDOM_CHUNK)
            makeRandomBlock(voxels, colours);
        else if (type == LIGHT_CHUNK)
            makeLightBlock(voxels, colours);
        else
            makeDebugBlock(voxels, colours);
        

    }

    void makeEmptyBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {

        Voxel voxel = {0, VoxelTypes::Empty};
        voxels = std::move(std::vector<Voxel>(BLOCK_VOLUME, voxel));
        colours = { {0,0,0,0}};

    }

    void makeGrassBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        Voxel voxel_dirt = {1, VoxelTypes::Dirt};
        Voxel voxel_grass = {2, VoxelTypes::Grass};
        Voxel voxel_grass2 = {3, VoxelTypes::Grass};
        std::vector<Voxel> these_voxels(BLOCK_VOLUME, voxel_dirt);



        //int y = BLOCK_SIZE-1;
        for (unsigned y = 0; y < BLOCK_SIZE; y++)
        {
            for (unsigned z = 0; z < BLOCK_SIZE; z++) 
            {
                for (unsigned x = 0; x < BLOCK_SIZE; x++)
                {
                    if (y > BLOCK_SIZE-3)
                    {
                        int index = indexFromXYZ(x,y,z);
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
 
    void makeRevealEarthBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        Voxel voxel = {1, VoxelTypes::Dirt};
        Voxel voxel2 = {2, VoxelTypes::Dirt};
        Voxel empty_vox = {0, VoxelTypes::Empty};
        std::vector<Voxel> these_voxels(BLOCK_VOLUME, voxel);
        /* int y = BLOCK_SIZE-1;

        for (unsigned z = 0; z < BLOCK_SIZE; z++) 
        {
            for (unsigned x = 0; x < BLOCK_SIZE; x++)
            {
                int index = indexFromXYZ(x,y,z, BLOCK_SIZE);
                
                    these_voxels[index] = empty_vox;
                
                
            }
        } */

        int y = BLOCK_SIZE-1;

        for (unsigned z = 0; z < BLOCK_SIZE; z++) 
        {
            for (unsigned x = 0; x < BLOCK_SIZE; x++)
            {
                int index = indexFromXYZ(x,y,z);
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

    void makeDirtBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        Voxel voxel = {1, VoxelTypes::Dirt};
        Voxel voxel2 = {2, VoxelTypes::Dirt};
        std::vector<Voxel> these_voxels(BLOCK_VOLUME, voxel);
        int y = BLOCK_SIZE-1;

        for (unsigned z = 0; z < BLOCK_SIZE; z++) 
        {
            for (unsigned x = 0; x < BLOCK_SIZE; x++)
            {
                if ( (rand() % 15) == 0)
                {
                    int index = indexFromXYZ(x,y,z);
                    these_voxels[index] = voxel2;
                }
                
            }
        }

        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {150, 100, 100, 255}, {120, 80, 80, 255}};
    }

    void makeTreeBlock  (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        Voxel tree_bark = {1, VoxelTypes::Tree};
        Voxel tree_inside = {2, VoxelTypes::Tree};
        std::vector<Voxel> block_voxels(BLOCK_VOLUME, tree_bark);
        unsigned offset = BLOCK_SIZE/8;
        unsigned sz_minus_off = (BLOCK_SIZE - 1) - offset;
        unsigned mid_lower_bound = sz_minus_off - (BLOCK_SIZE/2);
        unsigned mid_upper_bound = offset + (BLOCK_SIZE/2);
        for (unsigned y = 0; y < BLOCK_SIZE; y++)
        {
            for (unsigned z = 0; z < BLOCK_SIZE; z++) 
            {
                for (unsigned x = 0; x < BLOCK_SIZE; x++)
                {
                    if (
                        ( (x == offset || x == sz_minus_off) && (z >= offset && z <= sz_minus_off ) ) ||
                        ( (z == offset || z == sz_minus_off) && (x >= offset && x <= sz_minus_off ) ) ||
                        ( x > mid_lower_bound && z > mid_lower_bound && x < mid_upper_bound && z < mid_upper_bound )
                       )
                    {
                        int index = indexFromXYZ(x,y,z);
                        block_voxels[index] = tree_inside;
                    }
                }
            }
        }

        voxels = std::move(block_voxels);
        colours = { {0,0,0,0}, {110, 88, 82, 255}, {90, 70, 65, 255}};

    }

    void makeRandomBlock(std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        int num_colours = rand()%7+1;

        std::vector<Voxel> potential_voxels(num_colours); 
        potential_voxels[0] = {0, VoxelTypes::Empty};
        colours.push_back( {0,0,0,0} );
        for (int i = 1; i < num_colours; i++)
        {
            potential_voxels[i] = { (ColourID)(rand()%num_colours), VoxelTypes::Debug};
            colours.push_back({rand()%256, rand()%256, rand()%256, 255});
        }

        std::vector<Voxel> these_voxels(BLOCK_VOLUME);

        for (unsigned j = 0; j < BLOCK_VOLUME; j++)
        {
            these_voxels[j] = potential_voxels[rand() % num_colours];

        }

        voxels = std::move(these_voxels);



    }

    void makeDebugBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {
        std::vector<Voxel> these_voxels(BLOCK_VOLUME, {1, VoxelTypes::Debug});
        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {255, 0, 255, 255} };
    }

    void makeLightBlock (std::vector<Voxel>& voxels, std::vector<Colour>& colours)
    {

        std::vector<Voxel> these_voxels(BLOCK_VOLUME, {1, VoxelTypes::LightSrc});
        voxels = std::move(these_voxels);
        colours = { {0,0,0,0}, {255, 236, 178, 255} };
    }


}