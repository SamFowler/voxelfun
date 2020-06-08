#include "Sector.h"

std::pair<const BlockPos, const Block*> Sector::addBlock(const BlockPos& position, const BlockMakeType& type)
{
    std::vector<Voxel> voxels;
    voxels.reserve(sizeof(Voxel)*m_block_size*m_block_size*m_block_size);
    std::vector<Colour> colours;

    DefaultBlockMaker::makeBlock(type, voxels, colours, m_block_size);

    return addBlock(position, voxels, colours);
}

std::pair<const BlockPos, const Block*> Sector::addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours)
{
    unsigned int column_index = getBlockColumnIndexFromBlockPos(block_pos);
    if (m_block_column_details[column_index].isBlockEmpty(block_pos.y))
    {
        unsigned int block_index = getBlockIndexFromBlockPos(block_pos);
        m_blocks[block_index] = std::make_unique<Block>(voxels, colours, m_block_size);
        m_blocks[block_index]->updateAllNeighbours();
        m_blocks[block_index]->printBlock();

        if (m_block_column_details[column_index].addBlock(block_pos.y))
            return std::make_pair(block_pos, m_blocks[block_index].get() ); // if add block is visible, return it to be meshed
    }
    return std::make_pair(BlockPos(255,255,255), nullptr);
}

void Sector::editBlock(const BlockPos& block_pos /*, voxels/colours/changes */)
{
    //don't actually edit the block here, add it to list of blocks to update
    // this is done so updates are processed all at once in each frame
    
    //m_blocks_to_update.push_back(getBlockIndexFromBlockPos(block_pos)/*, <<<changes to make>>> */);
    m_blocks_to_update.push_back(block_pos /*, <<<changes to make>>> */);
}

void Sector::updateBlocks(std::vector<std::pair<const BlockPos, const Block*>> blocks_to_remesh)
{
    if (m_blocks_to_update.empty())
        return;
    
    //std::sort(m_blocks_to_update.begin(), m_blocks_to_update.end()); // sort indexes to be cache friendly

    for (auto block_pos : m_blocks_to_update)
    {
        unsigned int index = getBlockIndexFromBlockPos(block_pos);
        /* 
        //process block updates
        m_blocks[index].update( --voxels/colours/etc);
        */

       //if (change actually happend)
        blocks_to_remesh.push_back( std::make_pair(block_pos, m_blocks[index].get() ) );
    }

    m_blocks_to_update.clear();
    m_blocks_to_update.reserve(8*sizeof(BlockPos));
    
}


unsigned int Sector::getBlockIndexFromBlockPos(const BlockPos& block_pos)
{
    return (block_pos.z*16*8) + (block_pos.x*8) + block_pos.y;
}

unsigned int Sector::getBlockColumnIndexFromBlockPos(const BlockPos& block_pos)
{
    return (block_pos.z*16) + block_pos.x;
}
