#include "Block.h"

Block::Block (std::vector<Voxel> voxels)
 : m_voxel_data(std::move(voxels))
{
    std::cout << "block created" << std::endl;
}

uint32_t Block::getIndex (const VoxelPos& voxel_coord) const
{
    return (voxel_coord.y*BLOCK_SIZE_SQ) + (voxel_coord.z * BLOCK_SIZE) + voxel_coord.x;
}

VoxelPos Block::getVoxelPos(const uint32_t& index) const
{  
    return VoxelPos( {
        ( index      %  BLOCK_SIZE),
        ( index      / (BLOCK_SIZE_SQ)),
        ((index/BLOCK_SIZE)  %  BLOCK_SIZE)
    } );
}

bool Block::isBlockEdge  (const VoxelPos& voxel_coord) const
{
    return (
        voxel_coord.x == 0 || (voxel_coord.x + 1) == BLOCK_SIZE ||
        voxel_coord.y == 0 || (voxel_coord.y + 1) == BLOCK_SIZE ||
        voxel_coord.z == 0 || (voxel_coord.z + 1) == BLOCK_SIZE
    );
} 

bool Block::isBlockEdge(const uint32_t& voxel_index) const
{
    return isBlockEdge( getVoxelPos(voxel_index) );
}




void Block::setVoxels(const std::vector<VoxelPos>& voxel_coords, const VoxelType& type)
{
    for (auto it : voxel_coords)
        m_voxel_data[ getIndex(it) ].setType(type);
}

void Block::setVoxels(const std::vector<VoxelPos>& voxel_coords, const Voxel& voxel)
{ 
    for (auto it : voxel_coords)
        m_voxel_data[ getIndex(it) ] = voxel;
}

void Block::setVoxel(const VoxelPos& voxel_coord, const Voxel& voxel)
{ 
    m_voxel_data[ getIndex(voxel_coord) ] = voxel;
}


void Block::updateNeighbours(const VoxelPos& pos)
{
    Neighbours neighs;

    neighs.setXMinus( (pos.x     == 0         ) ? false : (getVoxel({pos.x - 1, pos.y    , pos.z    }).isVisible()) ) ;
    neighs.setXPlus ( (pos.x + 1 == BLOCK_SIZE) ? false : (getVoxel({pos.x + 1, pos.y    , pos.z    }).isVisible()) );
    neighs.setYMinus( (pos.y     == 0         ) ? false : (getVoxel({pos.x    , pos.y - 1, pos.z    }).isVisible()) );
    neighs.setYPlus ( (pos.y + 1 == BLOCK_SIZE) ? false : (getVoxel({pos.x    , pos.y + 1, pos.z    }).isVisible()) );
    neighs.setZMinus( (pos.z     == 0         ) ? false : (getVoxel({pos.x    , pos.y    , pos.z - 1}).isVisible()) );
    neighs.setZPlus ( (pos.z + 1 == BLOCK_SIZE) ? false : (getVoxel({pos.x    , pos.y    , pos.z + 1}).isVisible()) );
    //TODO replace the "false" with a check into neighbour blocks

    m_voxel_neighbours[ getIndex(pos) ] = neighs;
}

void Block::updateAllNeighbours()
{
    std::cout << "updating neighbours" << std::endl;
    //TODO test performance when looping 3 times like this or instead iterating through voxel vector
    //      make sure only doing one conversion between index and coords 
    for (unsigned int y = 0; y < BLOCK_SIZE; y++)
        for (unsigned int z = 0; z < BLOCK_SIZE; z++)
            for (unsigned int x = 0; x < BLOCK_SIZE; x++)
                updateNeighbours({x,y,z});

}
