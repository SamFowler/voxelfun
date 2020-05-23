#include "BlockManager.hpp"



/*
BlockManager::BlockManager(int& empty_block_size) :
    m_blocks(
    { 
        //initialise m_blocks with an empty block of size empty_block_size
        {empty_block_size, {(empty_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}}}
    })
 //       {{16, {0}, {0.0f, 0.0f, 0.0f, 0.0f}}})

//{ 
//{air_block_size, {(air_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}}}
//s}
{
    //Block(const unsigned int& size, std::vector<VoxelID>& voxels, const std::vector<Colour> colours)
    
    //Blocka b(a, {(a, 0)}, {{0.1,0.2,0.3,0.4}, {1,2,3,4}});

    //m_blocks.push_back({16, {0}, {0.0f, 0.0f, 0.0f, 0.0f}});
}
*/
BlockManager::BlockManager(const unsigned int& default_block_size, const int& numBlocks)
   // m_blocks(
   // { 
        //initialise m_blocks with an empty block of size empty_block_size at key 0
        //{0, {default_block_size, {(default_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}}} }
   //     std::make_unique<Block>({default_block_size, {(default_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}}})
  //  }default_block_size, {(default_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}}
 //   )
{
    //std::vector<VoxelID> voxels(default_block_size, 0);
   //std::vector<Colour> colours({{0.0f, 0.0f, 0.0f, 0.0f}});
    //Block block(default_block_size, {(default_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}} );
    m_blocks.reserve(numBlocks * sizeof(std::unique_ptr<Block>));
    m_blocks.push_back( std::make_unique<Block>(
        Block(default_block_size, {(default_block_size, 0)}, {{0.0f, 0.0f, 0.0f, 0.0f}} )
        ));
    //m_blocks.reserve(numBlocks * sizeof(Block));
}

// add a new block to the manager
BlockID BlockManager::addBlock(const Block& block)
{
    //TODO: work out if should use std::move to move block rather than copy it (i.e. m_blocks.emplace(..., std::move(block))
    //      may improve performance slightly?

    int new_block_id = 0;

    if (m_free_block_ids.empty()) 
    {
        new_block_id = m_blocks.size(); //index key of map end + 1
        m_blocks.push_back(std::make_unique<Block>(block));
    } 
    else 
    {
        new_block_id = m_free_block_ids.front();
        m_blocks[new_block_id] = std::make_unique<Block>(block);
        m_free_block_ids.pop();
    }

    return new_block_id;
}

BlockID BlockManager::addBlock(const unsigned int& size, const std::vector<VoxelID>& voxels, const std::vector<Colour> colours)
{
   return addBlock({size, voxels, colours});
}

// remove block from the manager
bool BlockManager::removeBlock(const BlockID& block_id)
{
    if (block_id != 0 && m_blocks[block_id] != nullptr)
    {
        m_blocks[block_id] = nullptr;
        m_free_block_ids.push(block_id);
        return true;
    }

    return false;
}

// get reference to block which is within the manager
const Block* BlockManager::getBlock(const BlockID& block_id) const
{

    return m_blocks[block_id].get();
}


// changes Voxel at voxel_index within Block at block_id to voxel_id
void BlockManager::changeVoxelsInBlock(const BlockID& block_id, const unsigned int& voxel_index, const VoxelID& voxel_id)
{
    m_blocks[block_id]->setVoxel(voxel_index, voxel_id);
}

void BlockManager::changeVoxelsInBlock(const BlockID& block_id, const std::vector<unsigned int>& voxel_indexes, const VoxelID& voxel_id)
{
    Block* block = m_blocks[voxel_id].get();

    for (auto it = voxel_indexes.begin(); it != voxel_indexes.end(); ++it)
    {
        //TODO: is this fast enough? Should this be performed within the Block to speed up?
        block->setVoxel(*it, voxel_id);
        //changeVoxelsInBlock(block_id, *it, voxel_id);
    }
}

void BlockManager::removeVoxelsFromBlock(const BlockID& block_id, const unsigned int& voxel_index)
{
    changeVoxelsInBlock(block_id, voxel_index, 0);
}

void BlockManager::removeVoxelsFromBlock(const BlockID& block_id, const std::vector<unsigned int>& voxel_indexes)
{
    changeVoxelsInBlock(block_id, voxel_indexes, 0);
}

void BlockManager::changeColourInBlock(const BlockID& block_id, const VoxelID& voxel_id, const VoxelID& replacement_id)
{
    m_blocks[block_id]->changeVoxelID(voxel_id, replacement_id);
}


// add a new colour to the Block at block_id. Returns id of this new colour
VoxelID BlockManager::addColourToBlock(const BlockID& block_id, const Colour& colour)
{
    return m_blocks[block_id]->addColour(colour);
}

// remove colour from block, sets voxels of that colour to empty
void BlockManager::removeColourFromBlock(const BlockID& block_id, const VoxelID& voxel_id)
{
    m_blocks[block_id]->removeColour(voxel_id);
}

