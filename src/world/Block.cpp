#include "Block.h"

//#include <iostream> //change to LOG for debug

#include "BlockManager.h"

Block::Block (Block block, BlockManager& manager_ptr)
    : m_voxel_data(std::move(block.getVoxelDataRef())),   m_block_colours(std::move(block.getColoursRef())),
      mp_manager  (manager_ptr),         m_position     (std::move(block.getPosition())),
      m_remesh    (true)
    {
        std::cout << "block created" << std::endl;
    }

Block::Block (const BlockPos& position, BlockManager& manager)
    : mp_manager(manager), m_position(position),
    m_remesh(true)
{
    
}


Block::Block (BlockPos position, std::vector<Voxel> voxels, std::vector<Colour> colours, BlockManager& manager)
    : m_voxel_data(std::move(voxels)),   m_block_colours(std::move(colours)),
      mp_manager  (manager),         m_position     (std::move(position)),
      m_remesh    (true)
    {
        std::cout << "block created" << std::endl;
    }

//Helpers
unsigned int  Block::indexFromInBlockPos     (const VoxelInBlockPos& voxel_coord) const
{
    return (voxel_coord.pos.y*mp_manager.m_block_size_sq) + (voxel_coord.pos.z * mp_manager.m_block_size) + voxel_coord.pos.x;
}

VoxelInBlockPos Block::inBlockPosFromIndex(const unsigned int& index) const
{  
    return VoxelInBlockPos( {
        ( index      %  mp_manager.m_block_size),
        ( index      / (mp_manager.m_block_size_sq)),
        ((index/mp_manager.m_block_size)  %  mp_manager.m_block_size)
    } );
}

glm::ivec3 xyz(int ind, int sz)
{
    return glm::ivec3( {
        (ind % sz),
        (ind / (sz*sz)),
        ((ind/sz)  % sz)
    } );
}

bool Block::isBlockEdge  (const VoxelInBlockPos& voxel_coord) const
{
    return (
        voxel_coord.pos.x == 0 || (voxel_coord.pos.x + 1) == mp_manager.m_block_size ||
        voxel_coord.pos.y == 0 || (voxel_coord.pos.y + 1) == mp_manager.m_block_size ||
        voxel_coord.pos.z == 0 || (voxel_coord.pos.z + 1) == mp_manager.m_block_size
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
        m_remesh = true;
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

ColourID Block::getVoxelColourID(const VoxelInBlockPos& voxel_coord) const
{
    return m_voxel_data[ indexFromInBlockPos(voxel_coord) ].getColourId();
}

Colour Block::getVoxelColour(const VoxelInBlockPos& voxel_coord) const
{
    return m_block_colours[ m_voxel_data[ indexFromInBlockPos(voxel_coord) ].getColourId() ];
}

VoxelType Block::getVoxelType (const VoxelInBlockPos& voxel_coord) const
{
    return m_voxel_data[ indexFromInBlockPos(voxel_coord) ].getType();
}

const Voxel& Block::getVoxel(const VoxelInBlockPos& voxel_coord) const
{
    return m_voxel_data[ indexFromInBlockPos(voxel_coord) ];
}

// Returns the position of the first occupiable voxel at or directly above the input voxel position
VoxelInBlockPos Block::getTopVoxelPos (const VoxelInBlockPos& voxel_coord) const
{
    for (unsigned int y = voxel_coord.pos.y; y < mp_manager.m_block_size; y++)
    {
        if( getVoxel( {voxel_coord.pos.x, y, voxel_coord.pos.z} ).isOccupiable() )
        {
            return {voxel_coord.pos.x, y, voxel_coord.pos.z};
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

void Block::setVoxels(const std::vector<VoxelInBlockPos>& voxel_coords, const Colour& colour)
{
    ColourID id = addColour(colour);
    for (auto it : voxel_coords)
    {
        m_voxel_data[ indexFromInBlockPos(it) ].setColourId(id);
    }
    m_remesh = true;
}

void Block::setVoxels(const std::vector<VoxelInBlockPos>& voxel_coords, const VoxelType& type)
{
    for (auto it : voxel_coords)
    {
        m_voxel_data[ indexFromInBlockPos(it) ].setType(type);
    }
    m_remesh = true;
}

void Block::setVoxels(const std::vector<VoxelInBlockPos>& voxel_coords, const Voxel& voxel)
{ 
    for (auto it : voxel_coords)
    {
        m_voxel_data[ indexFromInBlockPos(it) ] = voxel;
    }
    m_remesh = true;
}


void Block::updateNeighbours(const VoxelInBlockPos& voxel_coord)
{

    // TODO a lot can be done with this functionality. A list of voxel updates should be created and stored in block data.
    //      Once the block is finished updating all its voxels it should go through this list again and update the neigbour information.
    //      It should then vist each of the neighbours of the updated voxels and update their neighbour info as it may 
    //      have changed due to their neighbour updating..

    uint8_t neighbours = 0x00;

    //if (isBlockEdge(voxel_coord))
     // set each of the 6 active bits of neighours to false if voxel is on that block edge or to the "isVisible" result of the neighbour in that direction
    neighbours |= ( (voxel_coord.pos.x     == 0                      ) ? false : (getVoxel({voxel_coord.pos.x - 1, voxel_coord.pos.y    , voxel_coord.pos.z    }).isVisible()) ) << 0;
    neighbours |= ( (voxel_coord.pos.x + 1 == mp_manager.m_block_size) ? false : (getVoxel({voxel_coord.pos.x + 1, voxel_coord.pos.y    , voxel_coord.pos.z    }).isVisible()) ) << 1;
    neighbours |= ( (voxel_coord.pos.y     == 0                      ) ? false : (getVoxel({voxel_coord.pos.x    , voxel_coord.pos.y - 1, voxel_coord.pos.z    }).isVisible()) ) << 2;
    neighbours |= ( (voxel_coord.pos.y + 1 == mp_manager.m_block_size) ? false : (getVoxel({voxel_coord.pos.x    , voxel_coord.pos.y + 1, voxel_coord.pos.z    }).isVisible()) ) << 3;
    neighbours |= ( (voxel_coord.pos.z     == 0                      ) ? false : (getVoxel({voxel_coord.pos.x    , voxel_coord.pos.y    , voxel_coord.pos.z - 1}).isVisible()) ) << 4;
    neighbours |= ( (voxel_coord.pos.z + 1 == mp_manager.m_block_size) ? false : (getVoxel({voxel_coord.pos.x    , voxel_coord.pos.y    , voxel_coord.pos.z + 1}).isVisible()) ) << 5;
        //TODO replace the "false" with a check into neighbour blocks

  
    //std::cout << std::hex << (int)neighbours << std::endl;
    m_voxel_data[ indexFromInBlockPos(voxel_coord) ].setNeighbours(neighbours);
}

void Block::updateAllNeighbours()
{
    std::cout << "updating neighbours" << std::endl;
    //TODO test performance when looping 3 times like this or instead iterating through voxel vector
    //      make sure only doing one conversion between index and coords 
    for (unsigned int y = 0; y < mp_manager.m_block_size; y++)
    {
        for (unsigned int z = 0; z < mp_manager.m_block_size; z++)
        {
            for (unsigned int x = 0; x < mp_manager.m_block_size; x++)
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
        it.setColourId(id);
    }
    m_remesh = true;
}

void Block::changeAllVoxels(const VoxelType& type)
{
    for (auto& it : m_voxel_data)
    {
        it.setType(type);
    }
    m_remesh = true;
}

void Block::changeAllVoxels(const Voxel& voxel)
{
    for (auto& it : m_voxel_data)
    {
        it = voxel;
    }
    m_remesh = true;
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
    m_remesh = true;
}

void Block::changeVoxelsFromTo(const VoxelType& from_type, const VoxelType& to_type)
{
    for (auto& it : m_voxel_data)
    {
        if (it.getType() == from_type)
            it.setType(to_type);
    }
    m_remesh = true;
}

void Block::changeVoxelsFromTo(const Voxel& from_voxel, const Voxel& to_voxel)
{
    for (auto& it : m_voxel_data)
    {
        if (it == from_voxel)
            it = to_voxel;
    }
    m_remesh = true;
}

void Block::printBlock(const bool printVoxels) const
{
    std::cout << "[Block] pos{" << m_position.pos.x << " " << m_position.pos.y << " " << m_position.pos.x << "}, num_voxels{" <<
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