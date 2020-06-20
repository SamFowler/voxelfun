#include "BlockTree.h" 

#include "BlockNode.h"

uint8_t BlockTree::getOctantContainingPos(const BlockPos& pos) const
{
    uint8_t oct = 0;
    if (pos.x >= m_origin.x) oct |= 1;
    if (pos.y >= m_origin.y) oct |= 4;
    if (pos.z >= m_origin.z) oct |= 2;
    return oct;
}


void BlockTree::draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws) 
{


    for (int i = 0; i < 8; ++i)
    {
        if (m_children[i] != nullptr)
            m_children[i]->draw(frustum, uniforms, num_draws);
    }
};

void BlockTree::addBlock(const BlockPos& pos, BlockNode& block_node)
{
    uint8_t octant = getOctantContainingPos(pos);

    if (m_half_size.x == 1 )
    {
        m_children[octant] = std::make_unique<BlockNode>(std::move(block_node));
        m_children[octant]->setOrigin(pos);
    }
    else if (m_children[octant] != nullptr)
    {
        m_children[octant]->addBlock(pos, block_node);
    }
    else //next level of octree has not been set, set it
    {
        glm::uvec3 new_origin = m_origin;
        new_origin.x += m_half_size.x * (octant & 1 ? 0.5f : -0.5f);
        new_origin.y += m_half_size.y * (octant & 4 ? 0.5f : -0.5f);
        new_origin.z += m_half_size.z * (octant & 2 ? 0.5f : -0.5f);
        m_children[octant] = std::make_unique<BlockTree>(new_origin, m_half_size/2U);
        m_children[octant]->addBlock(pos, block_node);
    }
}

void BlockTree::deleteBlock(const BlockPos& pos)
{
    uint8_t octant = getOctantContainingPos(pos);

    if ( m_half_size.x == 2 )
    {   // we are at leaf level of octree - delete the block
        m_children[octant].reset(nullptr);
    }
    else if (m_children[octant] != nullptr)
    {
        m_children[octant]->deleteBlock(pos);

        if (m_children[octant]->isEmpty())
            m_children[octant].reset(nullptr); // delete child if it is completely empty
    }
    // else next level of octree == nullptr, so already does not exist
}

bool BlockTree::isEmpty()
{
    for (const auto& it : m_children)
    {
        if (it != nullptr)
            return false;
    }
    return true;
}