#include "Sector.h"

#include "../renderers/BlockMeshGenerator.h"

#include "../scenegraph/BlockNode.h"

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
    uint32_t block_index = getIndex(block_pos);
    uint32_t column_index = getColumnIndex(block_pos);

    if (m_block_column_details[column_index].isBlockEmpty(block_pos.y))
    {
        m_blocks[block_index] = std::make_unique<Block>(voxels);
        m_blocks[block_index]->updateAllNeighbours();

        m_block_column_details[column_index].addBlock(block_pos.y);

        blocks_to_mesh.emplace(block_pos);
    }
    return m_blocks[block_index].get();
}

void Sector::makeMeshes()
{

    if (blocks_to_mesh.empty())
            return; 
    int i = 0;
    while (i < 3) 
    {            
        BlockPos block_pos = blocks_to_mesh.front();
        updateBlockNeighbours(block_pos);

        glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(0.4, 0.4, 0.4));
        model = glm::translate(model, glm::vec3(block_pos) * (float)BLOCK_SIZE);

        BlockNode node = {model/* glm::mat4(1.0) */, 
                    BlockMeshGenerator::makeBlockVAO(*(m_blocks[getIndex(block_pos)].get() ), colours, BlockMeshGenerator::GREEDY_MESH)};
        m_block_tree.addBlock(block_pos, node);

        blocks_to_mesh.pop();
        if (blocks_to_mesh.empty())
            break;

        i++;
    }

}

void Sector::updateBlockNeighbours(const BlockPos& block_pos)
{
    unsigned int block_index = getIndex(block_pos);
    m_blocks[block_index]->updateAllNeighbours();
}

Block* Sector::getBlock(const BlockPos& block_pos)
{
    uint32_t column_index = getColumnIndex(block_pos);
    if (m_block_column_details[column_index].isBlockEmpty(block_pos.y))
        return addBlock(block_pos, BlockMakeType::EMPTY_CHUNK);
    else
        return m_blocks[getIndex(block_pos)].get();
}


uint32_t Sector::getIndex(const BlockPos& block_pos)
{
    return (block_pos.z*SECTOR_WIDTH_SQ) + (block_pos.x*SECTOR_WIDTH) + block_pos.y;
}

uint32_t Sector::getColumnIndex(const BlockPos& block_pos)
{
    return (block_pos.z*SECTOR_WIDTH) + block_pos.x;
}

void Sector::draw(const Uniforms& uniforms)
{
    m_block_tree.draw(uniforms);
}