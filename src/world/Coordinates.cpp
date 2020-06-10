#include "Coordinates.h"


namespace CoordinateConversion
{
    //TODO make these into a singleton?

SectorPos getSectorPos(const WorldPos& world_pos)
{
    unsigned int sector_size = 16;
    unsigned int sector_height = 8;
    unsigned int block_size = 32;
    return {
        ((world_pos.x - ((int)(world_pos.x % (sector_size   * block_size)))) / ((int)(sector_size   * block_size))),
        ((world_pos.y - ((int)(world_pos.y % (sector_height * block_size)))) / ((int)(sector_height * block_size))),
        ((world_pos.z - ((int)(world_pos.z % (sector_size   * block_size)))) / ((int)(sector_size   * block_size))),
    };
}
BlockPos getBlockPos(const WorldPos& world_pos)
{
    unsigned int sector_size = 16;
    unsigned int sector_height = 8;
    unsigned int block_size = 32;
    return {
        ((int)((world_pos.x % (sector_size   * block_size)) / block_size)),
        ((int)((world_pos.y % (sector_height * block_size)) / block_size)),
        ((int)((world_pos.z % (sector_size   * block_size)) / block_size))
    };
}
VoxelPos getVoxelPos(const WorldPos& world_pos)
{
    unsigned int sector_size = 16;
    unsigned int sector_height = 8;
    unsigned int block_size = 32;
    return {
        ((world_pos.x % (sector_size   * block_size)) % block_size),
        ((world_pos.y % (sector_height * block_size)) % block_size),
        ((world_pos.z % (sector_size   * block_size)) % block_size)
    };
}

WorldPos getWorldPos(const SectorPos& sector_pos, const BlockPos& block_pos, const VoxelPos& voxel_pos)
{
    unsigned int sector_size = 16;
    unsigned int sector_height = 8;
    unsigned int block_size = 32;

    return {
        (sector_pos.x * sector_size   * block_size) + (block_pos.x * block_size) + voxel_pos.x,
        (sector_pos.y * sector_height * block_size) + (block_pos.y * block_size) + voxel_pos.y,
        (sector_pos.z * sector_size   * block_size) + (block_pos.z * block_size) + voxel_pos.z,
    };
}

WorldPos getWorldPos(const SectorPos& sector_pos, const BlockPos& block_pos)
{
    unsigned int sector_size = 16;
    unsigned int sector_height = 8;
    unsigned int block_size = 32;

    return {
        (sector_pos.x * sector_size   * block_size) + (block_pos.x * block_size),
        (sector_pos.y * sector_height * block_size) + (block_pos.y * block_size),
        (sector_pos.z * sector_size   * block_size) + (block_pos.z * block_size),
    };
}

}