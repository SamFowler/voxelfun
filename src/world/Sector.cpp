#include "Sector.h"

#include "../renderers/BlockMeshGenerator.h"

#include "../scenegraph/BlockNode.h"

#include "SectorManager.h"

Block* Sector::addBlock(const BlockPos& position, const BlockMakeType& type)
{
    std::vector<Voxel> voxels;
    voxels.reserve(sizeof(Voxel) * BLOCK_VOLUME);
    std::vector<Colour> colours;

    DefaultBlockMaker::makeBlock(type, voxels, colours);

    return addBlock(position, voxels);
}
 
Block* Sector::addBlock(const BlockPos& block_pos, const std::vector<Voxel>& voxels)
{
    auto it = m_blocks.find(block_pos);
    if ( it == m_blocks.cend() )
    {
        blocks_to_mesh.emplace(block_pos);
        return m_blocks.emplace(block_pos, std::make_unique<Block>(voxels)).first->second.get();
    }
    return nullptr;

}

void Sector::makeMeshes(const SectorManager* sector_manager, const SectorPos& sector_pos)
{

    if (blocks_to_mesh.empty())
            return; 
    int i = 0;
    while (i < 3) 
    {            
        BlockPos block_pos = blocks_to_mesh.front();
        m_blocks[block_pos]->updateAllNeighbours( sector_manager->getBlockNeighbours(sector_pos, block_pos) );
        
        //glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(0.4, 0.4, 0.4));
        glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(1.0, 1.0, 1.0));
        model = glm::translate(model, glm::vec3(block_pos) * (float)BLOCK_SIZE);

        BlockNode node = {model/* glm::mat4(1.0) */, 
                    BlockMeshGenerator::makeBlockVAO(*(m_blocks[block_pos].get() ), colours, BlockMeshGenerator::GREEDY_MESH)};
        m_block_tree.addBlock(block_pos, node);

        blocks_to_mesh.pop();
        if (blocks_to_mesh.empty())
            break;

        i++;
    }

}


Block* Sector::getBlock(const BlockPos& block_pos)
{
    auto it = m_blocks.find(block_pos);
    if ( it != m_blocks.cend() )
        return it->second.get();
    else
        return nullptr;
}


uint32_t Sector::getIndex(const BlockPos& block_pos)
{
    return (block_pos.z*SECTOR_WIDTH_SQ) + (block_pos.x*SECTOR_WIDTH) + block_pos.y;
}

uint32_t Sector::getColumnIndex(const BlockPos& block_pos)
{
    return (block_pos.z*SECTOR_WIDTH) + block_pos.x;
}

void Sector::draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws)
{
    colours.texture.bind();
    m_block_tree.draw(frustum, uniforms, num_draws);
}