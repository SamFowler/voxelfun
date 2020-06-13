#include "Block.h"

Block::Block (std::vector<Voxel> voxels, std::vector<Colour> colours)
    : m_voxel_data(std::move(voxels)),   m_block_colours(std::move(colours))
    {
        std::cout << "block created" << std::endl;
    }

//Helpers
unsigned int  Block::indexFromVoxelPos     (const VoxelPos& voxel_coord) const
{
    return (voxel_coord.y*BLOCK_SIZE_SQ) + (voxel_coord.z * BLOCK_SIZE) + voxel_coord.x;
}

VoxelPos Block::inBlockPosFromIndex(const unsigned int& index) const
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

bool Block::isBlockEdge(const int& voxel_index) const
{
    return isBlockEdge( inBlockPosFromIndex(voxel_index) );
}

ColourID Block::addColour(const Colour& colour)
{
    ColourID id = findColour(colour);
    if (id)
    {
        return id;
    }
    else
    {
        if ( m_free_colour_ids.empty() )
        {
            m_block_colours.push_back(colour);
            return m_block_colours.size() - 1;
        }
        else
        {
            id = m_free_colour_ids.front();
            m_block_colours[ id ] = colour;
            m_free_colour_ids.pop();
            return id;
        }
    }
}

void Block::removeAllColours()
{
    m_block_colours.clear();
    m_block_colours.reserve(8 * sizeof(Colour));
    m_block_colours.push_back(Colour());
    std::queue<ColourID>().swap(m_free_colour_ids); 
}

void Block::removeColour (const Colour& colour)
{
    ColourID id = findColour(colour);
    removeColour(id);
}

void Block::removeColour (const ColourID& colour_id)
{
    if (colour_id != 0)
    {
        m_block_colours[colour_id] = {0, 0, 0, 0};
        m_free_colour_ids.push(colour_id);

        //TODO: set the removes colour voxels to something
    }
    
}

ColourID Block::findColour (const Colour& colour) const
{   
    ColourID id = 0;
    for (auto it : m_block_colours)
    {
        if (it == colour)
            return id;
        id++;
    }
    return 0;
}



// Getters

Colour Block::getColour(const ColourID& colour_id) const
{
    return m_block_colours[colour_id];
}

ColourID Block::getVoxelColourID(const VoxelPos& voxel_coord) const
{
    return m_voxel_data[ indexFromVoxelPos(voxel_coord) ].getColourId();
}

Colour Block::getVoxelColour(const VoxelPos& voxel_coord) const
{
    return m_block_colours[ m_voxel_data[ indexFromVoxelPos(voxel_coord) ].getColourId() ];
}

VoxelType Block::getVoxelType (const VoxelPos& voxel_coord) const
{
    return m_voxel_data[ indexFromVoxelPos(voxel_coord) ].getType();
}

const Voxel& Block::getVoxel(const VoxelPos& voxel_coord) const
{
    return m_voxel_data[ indexFromVoxelPos(voxel_coord) ];
}

Voxel&    Block::getVoxel        (const VoxelPos& voxel_coord)
{
    return m_voxel_data[ indexFromVoxelPos(voxel_coord) ];
}


// Returns the position of the first occupiable voxel at or directly above the input voxel position
VoxelPos Block::getTopVoxelPos (const VoxelPos& voxel_coord) const
{
    for (unsigned int y = voxel_coord.y; y < BLOCK_SIZE; y++)
    {
        if( getVoxel( {voxel_coord.x, y, voxel_coord.z} ).isOccupiable() )
        {
            return {voxel_coord.x, y, voxel_coord.z};
        }
    }
    return voxel_coord; // TODO: check blocks above or return top of the block instead
}

const std::vector<Voxel>& Block::getVoxelDataRef() const
{
    return m_voxel_data;
}

const std::vector<Colour>& Block::getColoursRef() const
{
    return m_block_colours;
}



// Setters

void Block::setVoxels(const std::vector<VoxelPos>& voxel_coords, const Colour& colour)
{
    ColourID id = addColour(colour);
    for (auto it : voxel_coords)
    {
        m_voxel_data[ indexFromVoxelPos(it) ].setColourId(id);
    }
}

void Block::setVoxels(const std::vector<VoxelPos>& voxel_coords, const VoxelType& type)
{
    for (auto it : voxel_coords)
    {
        m_voxel_data[ indexFromVoxelPos(it) ].setType(type);
    }
}

void Block::setVoxels(const std::vector<VoxelPos>& voxel_coords, const Voxel& voxel)
{ 
    for (auto it : voxel_coords)
    {
        m_voxel_data[ indexFromVoxelPos(it) ] = voxel;
    }
}

void Block::setVoxel(const VoxelPos& voxel_coord, const Voxel& voxel)
{ 
    m_voxel_data[ indexFromVoxelPos(voxel_coord) ] = voxel;
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

    m_voxel_neighbours[ indexFromVoxelPos(pos) ] = neighs;
}

void Block::updateAllNeighbours()
{
    std::cout << "updating neighbours" << std::endl;
    //TODO test performance when looping 3 times like this or instead iterating through voxel vector
    //      make sure only doing one conversion between index and coords 
    for (unsigned int y = 0; y < BLOCK_SIZE; y++)
    {
        for (unsigned int z = 0; z < BLOCK_SIZE; z++)
        {
            for (unsigned int x = 0; x < BLOCK_SIZE; x++)
            {
                updateNeighbours({x,y,z});
            }
        }
    }

}


void Block::changeAllVoxels(const Colour& colour)
{
    removeAllColours();
    ColourID id = addColour(colour);
    for (auto& it : m_voxel_data)
    {
        if (it.isVisible())
            it.setColourId(id);
    }
}

void Block::changeAllVoxels(const VoxelType& type)
{
    for (auto& it : m_voxel_data)
    {
        it.setType(type);
    }
}

void Block::changeAllVoxels(const Voxel& voxel)
{
    for (auto& it : m_voxel_data)
    {
        it = voxel;
    }
}

void Block::changeVoxelsFromTo(const Colour& from_colour, const Colour& to_colour)
{
    ColourID from_id = findColour(from_colour);
    ColourID to_id = addColour(to_colour);
    for (auto& it : m_voxel_data)
    {
        if (it.getColourId() == from_id)
            it.setColourId(to_id);
    }
}

void Block::changeVoxelsFromTo(const VoxelType& from_type, const VoxelType& to_type)
{
    for (auto& it : m_voxel_data)
    {
        if (it.getType() == from_type)
            it.setType(to_type);
    }
}

void Block::changeVoxelsFromTo(const Voxel& from_voxel, const Voxel& to_voxel)
{
    for (auto& it : m_voxel_data)
    {
        if (it == from_voxel)
            it = to_voxel;
    }
}

void Block::printBlock(const bool printVoxels) const
{
    //std::cout << "[Block] pos{" << m_position.x << " " << m_position.y << " " << m_position.x << "}, num_voxels{" <<
    std::cout << "[Block] num_voxels{" <<
            m_voxel_data.size() << "}, colours{";
    for (auto it : m_block_colours)
    {
        it.logColour(); std::cout << ", ";

    }
    std::cout << "} " << std::endl;
    if (printVoxels)
    {
        std::cout << "    voxels {";
        for (auto it : m_voxel_data)
        {
            it.logVoxel(); std::cout << ", ";
        }
        std::cout << "} " << std::endl;
    }
}