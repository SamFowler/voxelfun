#include "TerrainGenerator.h"

#include "../helpers/OpenSimplexNoise.h"

#include "WorldConstants.h"

TerrainGenerator::TerrainGenerator(int seed) 
    : m_seed(seed)
{
    m_simplex_generator = OpenSimplexNoise(seed);
};
/* 
void TerrainGenerator::generateBlock(Block& block, const WorldPos& block_origin)
{
    //OpenSimplexNoise noise_generator(m_seed);

    //WorldPos column_pos = block_origin;
    glm::vec2 origin_pos = {block_origin.x, block_origin.z};
    glm::vec2 column_pos;
    glm::vec2 block_sizes = {BLOCK_SIZE, BLOCK_SIZE};
    double noise_val;

    Voxel grass(block.addColour({10, 170, 10, 255}), VoxelTypes::Grass);
    Voxel snow(block.addColour({240, 240, 240, 255}), VoxelTypes::Grass);
    Voxel water(block.addColour({0, 0, 130, 255}), VoxelTypes::Grass);
    Voxel mountain(block.addColour({180, 180, 180, 255}), VoxelTypes::Grass);
    unsigned rounded_noise;

    // for (unsigned int z = 0; z < BLOCK_SIZE; z++)
    // {
    //     for (unsigned int x = 0; x < BLOCK_SIZE; x++)
    //     {
    for (unsigned int z = 0; z < BLOCK_SIZE; z++)
    {
        for (unsigned int x = 0; x < BLOCK_SIZE; x++)
        {
            column_pos = (origin_pos + glm::vec2(x, z)) / block_sizes;

            double noise_val = m_simplex_generator.Evaluate(column_pos.x, column_pos.y);
            noise_val = (noise_val+1)/2;
            rounded_noise = (unsigned int)(noise_val*BLOCK_SIZE);

            std::cout << "pos[" << column_pos.x << "," << column_pos.y << "], noise_val[" << rounded_noise << "]" << std::endl;
            
            for (unsigned int y = 0; y < BLOCK_SIZE; y++)
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
} */

double TerrainGenerator::getNoise(OpenSimplexNoise& simplex_gen, const glm::vec2& pos)
{
    return (simplex_gen.Evaluate(pos.x, pos.y) + 1) / 2;
}

double TerrainGenerator::getNoise(OpenSimplexNoise& simplex_gen, const glm::vec3& pos)
{
    return getNoise(simplex_gen, {pos.x, pos.z});
}

std::vector<std::pair<const BlockPos, Block &>> TerrainGenerator::generateSector(Sector* sector, const SectorPos& sector_pos)
{
    std::vector<std::pair<const BlockPos, Block &>> blocks_to_mesh;
    //OpenSimplexNoise noise_generator(m_seed);

    glm::uvec3 height_map_coord;

    ColourID colour = sector->colours.addColour(VoxelTypes::Grass, {10, 170, 10, 255});
    Voxel grass(colour, VoxelTypes::Grass);
    //Voxel grass(block_pair.second.addColour({10, 170, 10, 255}), VoxelTypes::Grass);

    int height_map[512][512];
    //Voxel grass(block_pair.second.addColour({10, 170, 10, 255}), VoxelTypes::Grass);

    for (unsigned block_z = 0; block_z < 4; block_z++)
    {
        for (unsigned block_x = 0; block_x < 4; block_x++)
        {
            BlockPos column_pos(block_x, 0, block_z);
            WorldPos column_world_pos = CoordinateConversion::getWorldPos(sector_pos, column_pos);

            glm::vec3 noise_pos;
            unsigned rounded_noise;
            int local_height_map[32][32];

            unsigned min_val = 10000;
            unsigned max_val = 0;

            for (unsigned voxel_z = 0; voxel_z < BLOCK_SIZE; voxel_z++)
            {
                for (unsigned voxel_x = 0; voxel_x < BLOCK_SIZE; voxel_x++)
                {
                    noise_pos = (column_world_pos + WorldPos(voxel_x, 0, voxel_z));
                    //noise_pos *= 0.01; //spreads the noise -> lower value = less frequent changes
                    noise_pos /= (SECTOR_TIMES_BLOCK_HEIGHT);
                                                                             //freq   //amplitude
                    double noise_val = getNoise(m_simplex_generator, noise_pos * 0.75f) * 0.25
                                     + getNoise(m_simplex_generator, noise_pos * 2.0f)  * 0.1
                                     + getNoise(m_simplex_generator, noise_pos * 16.0f)  * 0.01;
                    
                    //noise_val /= (1 + 0.5);
                    noise_val /= (0.25 + 0.1 + 0.01 ); //adjust for amplitude
                    

                    noise_val = std::pow(noise_val, 2);
                    // * 0.15; // change max amplitude of the noise
                    //noise_val = std::pow(noise_val, 0.5); // make valleys flatter


                    //noise_val = std::round(noise_val * 16) / 16; //terracing
                    rounded_noise = (unsigned int)(noise_val * SECTOR_TIMES_BLOCK_HEIGHT);
                    height_map_coord = (column_pos * (unsigned)BLOCK_SIZE) + glm::uvec3(voxel_x,0,voxel_z);
                    height_map[height_map_coord.z][height_map_coord.x] = rounded_noise;

                    local_height_map[voxel_z][voxel_x] = rounded_noise;

                    if (rounded_noise < min_val)
                        min_val = rounded_noise;
                    if (rounded_noise > max_val)
                        max_val = rounded_noise;

                    std::cout << "sector[" << voxel_x << "," << voxel_z << "], height val[" << local_height_map[voxel_z][voxel_x] << "]" << std::endl;

                }
            }

            min_val = min_val / BLOCK_SIZE;
            max_val = max_val / BLOCK_SIZE;

            for (unsigned block_y = min_val; block_y <= max_val; block_y++)
            {
                BlockPos block_pos = {block_x, block_y, block_z};
                std::pair<BlockPos, Block &> block_pair = sector->addBlock(SectorPos(block_pos), BlockMakeType::EMPTY_CHUNK);
                block_pair.first = SectorPos(block_pos) + (sector_pos * SECTOR_WIDTH);
                
                //Voxel grass(block_pair.second.addColour({10, 170, 10, 255}), VoxelTypes::Grass);
                for (unsigned int z = 0; z < BLOCK_SIZE; z++)
                {
                    for (unsigned int x = 0; x < BLOCK_SIZE; x++)
                    {
                        unsigned height_of_block = local_height_map[z][x] / BLOCK_SIZE;
                        if ( height_of_block == block_y)
                        {
                            unsigned voxel_height = local_height_map[z][x] % BLOCK_SIZE;

                            for (unsigned int y = 0; y <= voxel_height; y++)
                            {
                                // if (y >= voxel_height)
                                    // break;

                                block_pair.second.setVoxel({x,y,z}, grass);
                            }
                        }
                        else if ( height_of_block > block_y)
                        {
                            for (unsigned int y = 0; y < BLOCK_SIZE; y++)
                            {
                                // if (y >= voxel_height)
                                    // break;

                                block_pair.second.setVoxel({x,y,z}, grass);
                            }
                        }
                        


                        
                    }
                }
                blocks_to_mesh.push_back(block_pair);



                //m_terrain_generator.generateBlock(block_pair.second, CoordinateConversion::getWorldPos(sector_pos, block_pos, {0,0,0}));
                sector->updateBlockNeighbours(block_pos);
                //initial_mesh_list.push_back(block_pair);
            }
            
        }
    }

    return blocks_to_mesh;
           

}

