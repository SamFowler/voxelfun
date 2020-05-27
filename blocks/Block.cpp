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

void Block::makeNeighbours() 
{
        
    //int block_size = block.getSize();
    //std::vector<char> all_neighbours(block_size*block_size*block_size, 0);
    m_neighbours.clear();
    m_neighbours.reserve(sizeof(char)*m_size*m_size*m_size);

    int size = m_size;

    for (int y = 0; y < size; y++)
    {
        for (int z = 0; z < size; z++)
        {
            for (int x = 0; x < size; x++)
            {

                
                glm::ivec3 voxel_pos = {x,y,z};
                int voxel_index = (voxel_pos.x) + (voxel_pos.z * size) + (voxel_pos.y * size * size);

                VoxelID voxel_id = m_voxels[voxel_index];
                
                if (voxel_id <= 0)
                    continue;

                char byte = 0x00;

                if ( (voxel_pos.x == 0 || voxel_pos.y == 0 || voxel_pos.z == 0 || 
                    (voxel_pos.x + 1) == size || (voxel_pos.y + 1) == size || (voxel_pos.z + 1) == size) )
                {   //voxel is on edge of block so do safe checks
                    if (voxel_pos.x != 0) {
                        if (getVoxel({voxel_pos.x - 1, voxel_pos.y, voxel_pos.z}) )
                            byte |= 1UL << 0;
                    }
                    if (voxel_pos.x != size) {
                        if (getVoxel({voxel_pos.x + 1, voxel_pos.y, voxel_pos.z}) )
                            byte |= 1UL << 1;
                    }
                    if (voxel_pos.y != 0) {            
                        if (getVoxel({voxel_pos.x, voxel_pos.y - 1, voxel_pos.z}) )
                            byte |= 1UL << 2;
                    }
                    if (voxel_pos.y != size) {
                        if (getVoxel({voxel_pos.x, voxel_pos.y + 1, voxel_pos.z}) )
                            byte |= 1UL << 3;
                    }
                    if (voxel_pos.z != 0) {
                        if (getVoxel({voxel_pos.x, voxel_pos.y, voxel_pos.z - 1}) )
                            byte |= 1UL << 4;
                    }
                    if (voxel_pos.z != size) {
                        if (getVoxel({voxel_pos.x, voxel_pos.y, voxel_pos.z + 1}) )
                            byte |= 1UL << 5;
                    }
                }
                else //voxel isn't on edge of block
                { 
                    if (getVoxel({voxel_pos.x - 1, voxel_pos.y, voxel_pos.z}) )
                        byte |= 1UL << 0;
                    if (getVoxel({voxel_pos.x + 1, voxel_pos.y, voxel_pos.z}) )
                        byte |= 1UL << 1;
                    if (getVoxel({voxel_pos.x, voxel_pos.y - 1, voxel_pos.z}) )
                        byte |= 1UL << 2;
                    if (getVoxel({voxel_pos.x, voxel_pos.y + 1, voxel_pos.z}) )
                        byte |= 1UL << 3;
                    if (getVoxel({voxel_pos.x, voxel_pos.y, voxel_pos.z - 1}) )
                        byte |= 1UL << 4;
                    if (getVoxel({voxel_pos.x, voxel_pos.y, voxel_pos.z + 1}) )
                        byte |= 1UL << 5;
                }

                m_neighbours.push_back(byte);

            }
        }
    }

}
