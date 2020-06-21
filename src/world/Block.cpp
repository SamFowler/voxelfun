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




void Block::setVoxels(const std::vector<VoxelPos>& voxel_coords, const VoxelTypes& type)
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



void Block::updateNeighbours(const VoxelPos& pos, const std::array<const Block*, 6> block_neighbours)
{
    Neighbours neighs;

    neighs.setXMinus( (pos.x     == 0         ) ? block_neighbours[0]->getVoxel({BLOCK_SIZE-1, pos.y       ,        pos.z}).isOpaque() : (getVoxel({pos.x - 1, pos.y    , pos.z    }).isOpaque()) ) ;
    neighs.setXPlus ( (pos.x + 1 == BLOCK_SIZE) ? block_neighbours[1]->getVoxel({0           , pos.y       ,        pos.z}).isOpaque() : (getVoxel({pos.x + 1, pos.y    , pos.z    }).isOpaque()) );
    neighs.setYMinus( (pos.y     == 0         ) ? block_neighbours[2]->getVoxel({pos.x       , BLOCK_SIZE-1,        pos.z}).isOpaque() : (getVoxel({pos.x    , pos.y - 1, pos.z    }).isOpaque()) );
    neighs.setYPlus ( (pos.y + 1 == BLOCK_SIZE) ? block_neighbours[3]->getVoxel({pos.x       , 0           ,        pos.z}).isOpaque() : (getVoxel({pos.x    , pos.y + 1, pos.z    }).isOpaque()) );
    neighs.setZMinus( (pos.z     == 0         ) ? block_neighbours[4]->getVoxel({pos.x       , pos.y       , BLOCK_SIZE-1}).isOpaque() : (getVoxel({pos.x    , pos.y    , pos.z - 1}).isOpaque()) );
    neighs.setZPlus ( (pos.z + 1 == BLOCK_SIZE) ? block_neighbours[5]->getVoxel({pos.x       , pos.y       ,            0}).isOpaque() : (getVoxel({pos.x    , pos.y    , pos.z + 1}).isOpaque()) );
    
    //TODO replace the "false" with a check into neighbour blocks

    m_voxel_neighbours[ getIndex(pos) ] = neighs;
}

void Block::updateAllNeighbours(const std::array<const Block*, 6> block_neighbours)
{
    std::cout << "updating neighbours" << std::endl;
    //TODO test performance when looping 3 times like this or instead iterating through voxel vector
    //      make sure only doing one conversion between index and coords 
    for (unsigned int y = 0; y < BLOCK_SIZE; y++)
        for (unsigned int z = 0; z < BLOCK_SIZE; z++)
            for (unsigned int x = 0; x < BLOCK_SIZE; x++)
                updateNeighbours({x,y,z}, block_neighbours);

}
