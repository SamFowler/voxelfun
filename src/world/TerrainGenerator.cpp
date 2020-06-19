#include "TerrainGenerator.h"

#include "../helpers/OpenSimplexNoise.h"

#include "WorldConstants.h"

TerrainGenerator::TerrainGenerator(int seed) 
    : m_seed(seed)
{
    m_simplex_generator = OpenSimplexNoise(seed);
};

double TerrainGenerator::getNoise(OpenSimplexNoise& simplex_gen, const glm::vec2& pos)
{
    return (simplex_gen.Evaluate(pos.x, pos.y) + 1) / 2;
}

double TerrainGenerator::getNoise(OpenSimplexNoise& simplex_gen, const glm::vec3& pos)
{
    return getNoise(simplex_gen, {pos.x, pos.z});
}

void TerrainGenerator::addWorldColours(Sector& sector)
{
    sector.colours.addColour(VoxelTypes::Grass, {10, 170, 10, 255}  );
    sector.colours.addColour(VoxelTypes::Snow,  {240, 240, 240, 255});
    sector.colours.addColour(VoxelTypes::Water, {0, 0, 130, 255}    );
    sector.colours.addColour(VoxelTypes::Stone, {180, 180, 180, 255});
}

void TerrainGenerator::generateColumn(Sector& sector, const SectorPos& sector_pos, const BlockPos& block_pos)
{

    Voxel grass   (0, VoxelTypes::Grass);
    Voxel snow    (0, VoxelTypes::Snow );
    Voxel water   (0, VoxelTypes::Water);
    Voxel mountain(0, VoxelTypes::Stone); 

    WorldPos column_world_pos = CoordinateConversion::getWorldPos(sector_pos, block_pos);

    glm::vec3 noise_pos;

    uint32_t rounded_noise;
    uint32_t block_height_map[BLOCK_SIZE][BLOCK_SIZE];

    uint32_t min_val = 100000;
    uint32_t max_val = 0;

    // ==============================
    // Get height map for this column of blocks
    // ==============================
    for (uint32_t z = 0; z < BLOCK_SIZE; z++)
    {
        for (uint32_t x = 0; x < BLOCK_SIZE; x++)
        {
            noise_pos = {column_world_pos.x + x, 0, column_world_pos.z + z };
            //noise_pos *= 0.01; //spreads the noise -> lower value = less frequent changes
            noise_pos /= (SECTOR_TIMES_BLOCK_HEIGHT);
                                                                        //freq     //amplitude
            double noise_val =    getNoise(m_simplex_generator, noise_pos * 0.75f)  * 0.25
                                + getNoise(m_simplex_generator, noise_pos * 2.0f )  * 0.1
                                + getNoise(m_simplex_generator, noise_pos * 16.0f)  * 0.01;
            
            noise_val /= (0.25 + 0.1 + 0.01 ); //adjust for amplitude
            

            noise_val = std::pow(noise_val, 2);
            // * 0.15; // change max amplitude of the noise
            //noise_val = std::pow(noise_val, 0.5); // make valleys flatter

            //noise_val = std::round(noise_val * 16) / 16; //terracing

            rounded_noise = (uint32_t)(noise_val * SECTOR_TIMES_BLOCK_HEIGHT);

            block_height_map[z][x] = rounded_noise;

            if (rounded_noise < min_val)
                min_val = rounded_noise;
            if (rounded_noise > max_val)
                max_val = rounded_noise;

            // std::cout << "sector[" << voxel_x << "," << voxel_z << "], height val[" << local_height_map[voxel_z][voxel_x] << "]" << std::endl;
        } // end x loop
    } // end z loop



    // ==============================================
    // Create visible blocks in this column of blocks
    // ==============================================
    min_val = min_val / BLOCK_SIZE;
    max_val = max_val / BLOCK_SIZE;

    BlockPos block_column_pos = block_pos;
    std::vector<Block*> column_blocks;
    column_blocks.reserve( (max_val-min_val) * sizeof(Block*) );

    for (unsigned block_y = min_val; block_y <= max_val; block_y++)
    {
        block_column_pos.y = block_y;
        column_blocks.emplace_back(sector.addBlock(block_column_pos, BlockMakeType::EMPTY_CHUNK));
    }
 
    uint32_t height_of_block;
    uint32_t voxel_y;
    Block *block, *below_block;
    int32_t block_height_index;

    for (uint32_t z = 0; z < BLOCK_SIZE; z++)
    {
        for (uint32_t x = 0; x < BLOCK_SIZE; x++)
        {

            height_of_block = block_height_map[z][x] / BLOCK_SIZE;

            block_height_index = height_of_block - min_val;

            block = column_blocks[block_height_index];

            voxel_y = block_height_map[z][x] % BLOCK_SIZE;
            for (uint32_t y = 0; y <= voxel_y; y++)
                block->setVoxel({x,y,z}, grass);

            while (--block_height_index >= 0)
            {
                block = column_blocks[block_height_index];
                for (uint32_t y = 0; y < BLOCK_SIZE; y++)
                    block->setVoxel({x,y,z}, grass);
            }

        } // end x voxel loop
    } // end z voxel loop


}
