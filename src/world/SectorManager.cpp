#include "SectorManager.h"

#include "../Input.h"


void SectorManager::editSectors(Input& input)
{

}
 
Sector* SectorManager::getSector(const SectorPos& sector_pos) const
{
    auto it = m_sectors.find(sector_pos);
    if ( it != m_sectors.cend() )
    {
        return it->second.get();
    }  
    else
    {
        return nullptr;
    }
    
}

Sector* SectorManager::createSector(const SectorPos& sector_pos)
{
    return m_sectors.emplace(sector_pos, std::make_unique<Sector>()).first->second.get();
}

Block*  SectorManager::getBlock (const SectorPos& sector_pos, const BlockPos& block_pos) const
{
    Sector* sector = getSector(sector_pos);
    if (sector != nullptr)
        return sector->getBlock(block_pos);
    else
        return nullptr; 
}

Voxel& SectorManager::getVoxel(const SectorPos& sector_pos, const BlockPos& block_pos, const VoxelPos& voxel_pos) const
{
    return getBlock(sector_pos, block_pos)->getVoxel(voxel_pos);
}

Sector* SectorManager::addSector(const SectorPos& sector_pos)
{
    auto it = m_sectors.find(sector_pos);
    if ( it == m_sectors.cend() )
    {
        return m_sectors.emplace(sector_pos, std::make_unique<Sector>()).first->second.get();
    }
    return nullptr;
}

void SectorManager::generateWorld(const SectorPos& player_sector_pos, const BlockPos& player_block_pos)
{
    //TODO should be some kind of calculation based off of where the player / camera is within the world here
    
    Sector* p_sector = getSector(player_sector_pos);
    if (p_sector == nullptr)
    {
        p_sector = createSector(player_sector_pos);
        m_terrain_generator.addWorldColours(*p_sector);
    }

   
    m_terrain_generator.generateColumn( *p_sector, player_sector_pos, player_block_pos);

}

void SectorManager::update()
{
    SectorPos sector_pos = {0,0,0};
    auto sector = m_sectors.find(sector_pos);
    sector->second->makeMeshes(this, sector_pos);
}

void SectorManager::draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws)
{
    auto sector = m_sectors.find({0,0,0});
    sector->second->draw(frustum, uniforms, num_draws);
} 

std::array<const Block*, 6> SectorManager::getBlockNeighbours(const SectorPos& sector_pos, const BlockPos& block_pos) const
{
    std::array<const Block*, 6> neighbour_blocks;

    // x minus block neighbour
    if (block_pos.x != 0)
        neighbour_blocks[0] = getBlock(sector_pos, {block_pos.x - 1, block_pos.y, block_pos.z});
    else
        neighbour_blocks[0] = getBlock({sector_pos.x - 1, sector_pos.y, sector_pos.z}, {SECTOR_WIDTH - 1, block_pos.y, block_pos.z});

    //x plus block neighbour
    if (block_pos.x != (SECTOR_WIDTH - 1) )
        neighbour_blocks[1] = getBlock(sector_pos, {block_pos.x + 1, block_pos.y, block_pos.z});
    else
        neighbour_blocks[1] = getBlock({sector_pos.x + 1, sector_pos.y, sector_pos.z}, {0, block_pos.y, block_pos.z});
     
    // y minus block neighbour
    if (block_pos.y != 0)
        neighbour_blocks[2] = getBlock(sector_pos, {block_pos.x, block_pos.y - 1, block_pos.z});
    else
        neighbour_blocks[2] = getBlock({sector_pos.x, sector_pos.y - 1, sector_pos.z}, {block_pos.x, SECTOR_WIDTH - 1, block_pos.z});

    // y plus block neighbour
    if (block_pos.y != (SECTOR_WIDTH - 1))
        neighbour_blocks[3] = getBlock(sector_pos, {block_pos.x, block_pos.y + 1, block_pos.z});
    else
        neighbour_blocks[3] = getBlock({sector_pos.x, sector_pos.y + 1, sector_pos.z}, {block_pos.x, 0, block_pos.z});

    // z minus block neighbour
    if (block_pos.z != 0)
        neighbour_blocks[4] = getBlock(sector_pos, {block_pos.x, block_pos.y, block_pos.z - 1});
    else
        neighbour_blocks[4] = getBlock({sector_pos.x, sector_pos.y, sector_pos.z - 1}, {block_pos.x, block_pos.y, SECTOR_WIDTH - 1});

    // z plus block neighbour
    if (block_pos.z != (SECTOR_WIDTH - 1))
        neighbour_blocks[5] = getBlock(sector_pos, {block_pos.x, block_pos.y, block_pos.z + 1});
    else
        neighbour_blocks[5] = getBlock({sector_pos.x, sector_pos.y, sector_pos.z + 1}, {block_pos.x, block_pos.y, 0});

    for (int i = 0; i < 6; i++)
        if (neighbour_blocks[i] == nullptr)
            neighbour_blocks[i] = m_empty_block.get();

    return neighbour_blocks;
}