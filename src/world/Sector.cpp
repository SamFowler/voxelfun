#include "Sector.h"

const Block* Sector::addBlock(const BlockPos& position, const BlockMakeType& type)
{
    std::vector<Voxel> voxels;
    voxels.reserve(sizeof(Voxel)*m_block_size*m_block_size*m_block_size);
    std::vector<Colour> colours;

    DefaultBlockMaker::makeBlock(type, voxels, colours, m_block_size);

    return addBlock(position, voxels, colours);
}

const Block* Sector::addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours)
{
    unsigned int column_index = getBlockColumnIndexFromBlockPos(block_pos);
    if (m_block_column_details[column_index].isBlockEmpty(block_pos.y))
    {
        unsigned int block_index = getBlockIndexFromBlockPos(block_pos);
        m_blocks[block_index] = {block_pos, voxels, colours, m_block_size};
        m_blocks[block_index].updateAllNeighbours();
        m_blocks[block_index].printBlock();

        if (m_block_column_details[column_index].addBlock(block_pos.y))
            return &(m_blocks[block_index]); // if add block is visible, return it to be meshed
    }
    return nullptr;
}

void Sector::editBlock(const BlockPos& block_pos /*, voxels/colours/changes */)
{
    //don't actually edit the block here, add it to list of blocks to update
    // this is done so updates are processed all at once in each frame
    m_blocks_to_update.push_back(getBlockIndexFromBlockPos(block_pos)/*, <<<changes to make>>> */);
}

void Sector::updateBlocks(std::vector<const Block*> blocks_to_remesh)
{
    if (m_blocks_to_update.empty())
        return;
    
    std::sort(m_blocks_to_update.begin(), m_blocks_to_update.end()); // sort indexes to be cache friendly

    for (auto it : m_blocks_to_update)
    {
        /* 
        //process block updates
        m_blocks[it].update( --voxels/colours/etc);
        */

       //if (change actually happend)
        blocks_to_remesh.push_back( &(m_blocks[it]) );
    }

    m_blocks_to_update.clear();
    m_blocks_to_update.reserve(16*sizeof(unsigned int));
    
}


unsigned int Sector::getBlockIndexFromBlockPos(const BlockPos& block_pos)
{
    return (block_pos.z*16*8) + (block_pos.x*8) + block_pos.y;
}

unsigned int Sector::getBlockColumnIndexFromBlockPos(const BlockPos& block_pos)
{
    return (block_pos.z*16) + block_pos.x;
}

