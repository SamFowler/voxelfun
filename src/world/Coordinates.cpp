#include "Coordinates.h"

#include "WorldConstants.h"

namespace CoordinateConversion
{
    //TODO make these into a singleton?

SectorPos getSectorPos(const WorldPos& world_pos)
{
    return {
        ((world_pos.x - ((int)(world_pos.x % (SECTOR_TIMES_BLOCK_SIZE)))) / ((int)(SECTOR_TIMES_BLOCK_SIZE))),
        ((world_pos.y - ((int)(world_pos.y % (SECTOR_TIMES_BLOCK_HEIGHT)))) / ((int)(SECTOR_TIMES_BLOCK_HEIGHT))),
        ((world_pos.z - ((int)(world_pos.z % (SECTOR_TIMES_BLOCK_SIZE)))) / ((int)(SECTOR_TIMES_BLOCK_SIZE))),
    };
}
BlockPos getBlockPos(const WorldPos& world_pos)
{
    return {
        ((int)((world_pos.x % (SECTOR_TIMES_BLOCK_SIZE)) / BLOCK_SIZE)),
        ((int)((world_pos.y % (SECTOR_TIMES_BLOCK_HEIGHT)) / BLOCK_SIZE)),
        ((int)((world_pos.z % (SECTOR_TIMES_BLOCK_SIZE)) / BLOCK_SIZE))
    };
}
VoxelPos getVoxelPos(const WorldPos& world_pos)
{
    return {
        ((world_pos.x % (SECTOR_TIMES_BLOCK_SIZE)) % BLOCK_SIZE),
        ((world_pos.y % (SECTOR_TIMES_BLOCK_HEIGHT)) % BLOCK_SIZE),
        ((world_pos.z % (SECTOR_TIMES_BLOCK_SIZE)) % BLOCK_SIZE)
    };
}

WorldPos getWorldPos(const SectorPos& sector_pos, const BlockPos& block_pos, const VoxelPos& voxel_pos)
{
    return {
        (sector_pos.x * SECTOR_TIMES_BLOCK_SIZE) + (block_pos.x * BLOCK_SIZE) + voxel_pos.x,
        (sector_pos.y * SECTOR_TIMES_BLOCK_HEIGHT) + (block_pos.y * BLOCK_SIZE) + voxel_pos.y,
        (sector_pos.z * SECTOR_TIMES_BLOCK_SIZE) + (block_pos.z * BLOCK_SIZE) + voxel_pos.z,
    };
}

WorldPos getWorldPos(const SectorPos& sector_pos, const BlockPos& block_pos)
{
    return {
        (sector_pos.x * SECTOR_TIMES_BLOCK_SIZE) + (block_pos.x * BLOCK_SIZE),
        (sector_pos.y * SECTOR_TIMES_BLOCK_HEIGHT) + (block_pos.y * BLOCK_SIZE),
        (sector_pos.z * SECTOR_TIMES_BLOCK_SIZE) + (block_pos.z * BLOCK_SIZE),
    };
}

}