#include "Block.hpp"




void Block::changeVoxelID(const VoxelID& voxel_id, const VoxelID& replacement_id)
{
    for (auto it = m_voxels.begin(); it != m_voxels.end(); ++it)
    {
        if (*it == voxel_id)
        {
            *it = replacement_id;
        }
    }
}

void Block::removeColour(const VoxelID& colour_id)
{
    changeVoxelID(colour_id, 0);
    m_colours[colour_id] = {-1.0f, -1.0f, -1.0f, -1.0f};
}

VoxelID Block::addColour(const Colour& colour)
{
    for (unsigned int i = 0; i < m_colours.size(); ++i)
    {
        if (m_colours[i].r < 0.0f)
        {
            m_colours[i] = colour;
            return m_colours.size() - 1;
        }
    }

    m_colours.push_back(colour);
    return m_colours.size() - 1;
}
