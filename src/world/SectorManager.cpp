#include "SectorManager.h"

#include "../Input.h"

SectorManager::SectorManager(unsigned int block_size)
: m_block_size(block_size)
{
}

void SectorManager::editSectors(Input& input)
{

}

void SectorManager::updateSectors(std::vector<std::pair<const BlockPos, const Block*>> blocks_to_remesh)
{

}

Sector* SectorManager::addSector(const SectorPos& sector_pos)
{
    auto it = m_sectors.find(sector_pos);
    if ( it == m_sectors.cend() )
    {
        return m_sectors.emplace(sector_pos, std::make_unique<Sector>(m_block_size)).first->second.get();
    }
    return nullptr;
}
