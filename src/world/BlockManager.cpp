#include "BlockManager.h"

//#include <iostream> //TODO: replace with log
 
bool BlockManager::init() 
{
    /*
    //addBlock( {} )
    //Block (BlockPos position, std::vector<Voxel> voxels, std::vector<Colour> colours, BlockManager& manager_ptr);
    std::cout << "block manager init" << std::endl;
    BlockPos pos = {0,0,0};
    Voxel voxel = {1, VoxelType::Grass};
    std::vector<Voxel> voxels(m_block_volume, voxel);
    std::vector<Colour> colours = { {0,0,0,0}, {255, 0, 255, 255} };

    addBlock(
        pos, voxels, colours
    );*/

    return true;
}

void BlockManager::update(const Input& input) 
{

}

void BlockManager::destroy()
{

}

void BlockManager::addBlock(const BlockPos& position, const BlockMakeType& type)
{
    std::vector<Voxel> voxels;
    voxels.reserve(sizeof(Voxel)*m_block_volume);
    std::vector<Colour> colours;

    DefaultBlockMaker::makeBlock(type, voxels, colours, m_block_size);

    addBlock(position, voxels, colours);
}

void BlockManager::addBlock(const BlockPos& position, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours)
{
    
    auto it = m_blocks.find(position);
    if ( it == m_blocks.cend() )
    {
        
        std::cout << "Adding: " << std::endl;
        auto& block = m_blocks.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(position),
            std::forward_as_tuple(position, voxels, colours, *this)
        ).first->second;
        block.updateAllNeighbours();
        block.printBlock();
        std::cout << "block added" << std::endl;
        addBlockToUpdateList(position);
    }
}

void BlockManager::replaceBlock(const Block& block)
{
    m_blocks.emplace( 
        std::piecewise_construct,
        std::forward_as_tuple(block.getPosition()),
        std::forward_as_tuple(block)
        );
}

void BlockManager::addBlockToUpdateList(const BlockPos& block_pos)
{
    std::cout << "adding block to update list" << std::endl;
    for (auto it : m_updated_block_list)
    {
        if (it->getPosition() == block_pos)
        { // block_pos is already in list of blocks to update, don't add to list
            return;
        }
    }
    std::cout << "block added to update list" << std::endl;
    m_updated_block_list.push_back(getBlockPtr(block_pos));
    std::cout << "block added to update list" << std::endl;

}

void BlockManager::clearUpdatedBlockList()
{
    m_updated_block_list.clear();
}

std::vector<const Block*> BlockManager::getUpdatedBlockList() const
{
    return m_updated_block_list;
}

const Block* BlockManager::getBlockPtr(const BlockPos& block_pos) const
{
    auto it = m_blocks.find(block_pos);
    if (it != m_blocks.cend())
    {
        return &(it->second);
    }
    else
    {
        std::cout << "Could not find block: pos{" << block_pos.pos.x << "," << block_pos.pos.y << "," << block_pos.pos.z << "}" << std::endl;
    }
    
    return nullptr;
}
