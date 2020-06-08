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

void SectorManager::addSector(SectorPos& sector_pos)
{
    auto it = m_sectors.find(sector_pos);
    if ( it == m_sectors.cend() )
    {
        auto sector = m_sectors.emplace(sector_pos, std::make_unique<Sector>(m_block_size));
        /* 
        std::cout << "Adding: " << std::endl;
        auto& block = m_sectors.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(position),
            std::forward_as_tuple(position, voxels, colours, *this)
        ).first->second;
        block.updateAllNeighbours();
        block.printBlock();
        std::cout << "block added" << std::endl;
        addBlockToUpdateList(position); */
    }
}
