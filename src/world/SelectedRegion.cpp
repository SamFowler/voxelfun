#include "SelectedRegion.h"

#include "../Input.h"

SelectedRegion::SelectedRegion(const SectorPos sector_pos, const BlockPos block_pos, const VoxelPos voxel_pos,
                                unsigned int block_size, unsigned int sector_height, unsigned int sector_size) 
    : m_sector_pos(sector_pos), m_block_pos(block_pos), m_voxel_pos(voxel_pos),
    m_block_size(block_size), m_sector_height(sector_height), m_sector_size(sector_size)
{
    m_sect_times_block_sizes = m_sector_size * m_block_size;
    m_sect_height_times_block_size = sector_height * m_block_size;
}

void SelectedRegion::moveRegion(Input& input)
{
    bool hasMoved = false;
    unsigned move_speed = 1;
    if (input.isKeyHeld(SDLK_LALT))
        move_speed = 4;


    if (input.wasKeyPressed(SDLK_j))
    {
        m_world_pos.x -= move_speed;
        hasMoved = true;
    }

    if (input.wasKeyPressed(SDLK_l))
    {
        m_world_pos.x += move_speed;
        hasMoved = true;
    }


    if (input.wasKeyPressed(SDLK_k))
    {
        m_world_pos.y -= move_speed;
        hasMoved = true;
    }

    if (input.wasKeyPressed(SDLK_i))
    {
        m_world_pos.y += move_speed;
        hasMoved = true;
    }


    if (input.wasKeyPressed(SDLK_u))
    {
        m_world_pos.z -= move_speed;
        hasMoved = true;
    }

    if (input.wasKeyPressed(SDLK_o))
    {
        m_world_pos.z += move_speed;
        hasMoved = true;
    }

    if (hasMoved)
        printSelected();
}

WorldPos SelectedRegion::getWorldPos()
{
    return m_world_pos;
}

SectorPos SelectedRegion::getSectorPos()
{
    return {
        ((m_world_pos.x - ((int)(m_world_pos.x % (m_sector_size   * m_block_size)))) / ((int)(m_sector_size   * m_block_size))),
        ((m_world_pos.y - ((int)(m_world_pos.y % (m_sector_height * m_block_size)))) / ((int)(m_sector_height * m_block_size))),
        ((m_world_pos.z - ((int)(m_world_pos.z % (m_sector_size   * m_block_size)))) / ((int)(m_sector_size   * m_block_size))),
    };
}
BlockPos SelectedRegion::getBlockPos()
{
    return {
        ((int)((m_world_pos.x % (m_sector_size   * m_block_size)) / m_block_size)),
        ((int)((m_world_pos.y % (m_sector_height * m_block_size)) / m_block_size)),
        ((int)((m_world_pos.z % (m_sector_size   * m_block_size)) / m_block_size))
    };
}
VoxelPos SelectedRegion::getVoxelPos()
{
    return {
        ((m_world_pos.x % (m_sector_size   * m_block_size)) % m_block_size),
        ((m_world_pos.y % (m_sector_height * m_block_size)) % m_block_size),
        ((m_world_pos.z % (m_sector_size   * m_block_size)) % m_block_size)
    };
}

void SelectedRegion::printSelected()
{   
    m_sector_pos = getSectorPos();
    m_block_pos = getBlockPos();
    m_voxel_pos = getVoxelPos();

    std::cout << "[Selected]: world[" << m_world_pos.x  << ", " << m_world_pos.y << ", "  << m_world_pos.z << 
                         "], sector[" << m_sector_pos.x << ", " << m_sector_pos.y << ", " << m_sector_pos.z << 
                          "], block[" << m_block_pos.x  << ", " << m_block_pos.y  << ", " << m_block_pos.z  <<
                         " ], voxel[" << m_voxel_pos.x  << ", " << m_voxel_pos.y  << ", " << m_voxel_pos.z  << "]" << std::endl;
}