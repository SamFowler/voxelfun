#include "TerrainGenerator.h"

#include "../helpers/OpenSimplexNoise.h"



TerrainGenerator::TerrainGenerator(int seed) 
    : m_seed(seed)
{
};

void TerrainGenerator::generateBlock(Block& block, const WorldPos& block_origin)
{
    OpenSimplexNoise noise_generator(m_seed);
    unsigned block_size = 32;
    //WorldPos column_pos = block_origin;
    glm::vec2 origin_pos = {block_origin.x, block_origin.z};
    glm::vec2 column_pos;
    glm::vec2 block_sizes = {block_size, block_size};
    double noise_val;

    Voxel grass(block.addColour({10, 170, 10, 255}), VoxelType::Grass);
    Voxel snow(block.addColour({240, 240, 240, 255}), VoxelType::Grass);
    Voxel water(block.addColour({0, 0, 130, 255}), VoxelType::Grass);
    Voxel mountain(block.addColour({180, 180, 180, 255}), VoxelType::Grass);
    unsigned rounded_noise;

    for (unsigned int z = 0; z < block_size; z++)
    {
        for (unsigned int x = 0; x < block_size; x++)
        {
            column_pos = (origin_pos + glm::vec2(x, z)) / block_sizes;

            double noise_val = noise_generator.Evaluate(column_pos.x, column_pos.y);
            noise_val = (noise_val+1)/2;
            rounded_noise = (unsigned int)(noise_val*block_size);

            std::cout << "pos[" << column_pos.x << "," << column_pos.y << "], noise_val[" << rounded_noise << "]" << std::endl;
            
            for (unsigned int y = 0; y < block_size; y++)
            {
                std::cout << "";
                if (y >= rounded_noise)
                    break;

                if (y < 6)
                    block.setVoxel({x,y,z}, water);
                else if (y < 19)
                    block.setVoxel({x,y,z}, grass);
                else if (y < 21)
                    block.setVoxel({x,y,z}, mountain);
                else if (y < 32)
                    block.setVoxel({x,y,z}, snow);
            }

        }
    }
}

void TerrainGenerator::generateSector(Sector* sector, const SectorPos& sector_pos)
{

    OpenSimplexNoise noise_generator(m_seed);

    const unsigned sector_size = 16;
    const unsigned sector_height = 8;
    const unsigned block_size = 32;

    const unsigned sector_voxel_height = sector_height * block_size;

    glm::uvec3 height_map_coord;

    int height_map[256][256];

    for (unsigned block_z = 0; block_z < sector_size; block_z++)
    {
        for (unsigned block_x = 0; block_x < sector_size; block_x++)
        {
            BlockPos column_pos(block_x, 0, block_z);
            WorldPos column_world_pos = CoordinateConversion::getWorldPos(sector_pos, column_pos);

            WorldPos voxel_column_world_pos;
            unsigned rounded_noise;

            for (unsigned voxel_z = 0; voxel_z < block_size; voxel_z++)
            {
                for (unsigned voxel_x = 0; voxel_x < block_size; voxel_x++)
                {
                    voxel_column_world_pos = column_world_pos + WorldPos(voxel_x, 0, voxel_z);

                    double noise_val = noise_generator.Evaluate(voxel_column_world_pos.x, voxel_column_world_pos.z);
                    noise_val = (noise_val+1)/2; // set noise between 0 and 1
                    rounded_noise = (unsigned int)(noise_val * sector_voxel_height);

                    height_map_coord = (column_pos*block_size) + glm::uvec3(voxel_x,0,voxel_z);
                    height_map[height_map_coord.z][height_map_coord.x] = rounded_noise;

                    std::cout << "sector[" << height_map_coord.x << "," << height_map_coord.z << "], height val[" << height_map[height_map_coord.z][height_map_coord.x] << "]" << std::endl;
                }
            }

            
        }
    }


            for (unsigned sector_y = 0; sector_y < sector_size; sector_y++)
            {

            }

}

