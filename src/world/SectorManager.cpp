#include "SectorManager.h"

#include "../Input.h"


void SectorManager::editSectors(Input& input)
{

}

Sector* SectorManager::getSector(const SectorPos& sector_pos)
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

Block*  SectorManager::getBlock (const SectorPos& sector_pos, const BlockPos& block_pos)
{
    return getSector(sector_pos)->getBlock(block_pos);
}

Voxel& SectorManager::getVoxel(const SectorPos& sector_pos, const BlockPos& block_pos, const VoxelPos& voxel_pos)
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
    auto sector = m_sectors.find({0,0,0});
    sector->second->makeMeshes();
}

void SectorManager::draw(const Uniforms& uniforms)
{
    auto sector = m_sectors.find({0,0,0});
    sector->second->draw(uniforms);
} 

