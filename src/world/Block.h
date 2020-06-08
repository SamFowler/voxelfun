#pragma once

//#include <vector>
//#include <queue>
//#include <glm/vec3.h>

#include "../pch/pch_std.h"

#include "Voxel.h"
#include "Coordinates.h"
#include "Colour.h"


class BlockManager;

class Block
{
public:
    //Constructors
    Block ();
    Block (Block block, unsigned int& block_size);//BlockManager& manager_ptr);
    Block (unsigned int& block_size); //BlockManager& manager);
    Block (std::vector<Voxel> voxels, std::vector<Colour> colours, unsigned int& block_size); //BlockManager& manager);

    // Helpers
    unsigned int    indexFromVoxelPos   (const VoxelPos& voxel_coord) const;
    VoxelPos inBlockPosFromIndex   (const unsigned int&    index      ) const;

    bool isBlockEdge  (const VoxelPos& voxel_coord) const;
    bool isBlockEdge  (const int&             voxel_index) const;

    ColourID addColour(const Colour& colour);
    void removeColour (const Colour& colour);
    void removeColour (const ColourID& colour_id);
    void removeAllColours();
    ColourID findColour (const Colour& colour) const;

    // Getters
    //BlockPos    getPosition   () const  { return m_position;   }

    Colour     getColour       (const ColourID&        colour_id  ) const;
    ColourID   getVoxelColourID(const VoxelPos& voxel_coord) const;
    Colour     getVoxelColour  (const VoxelPos& voxel_coord) const;
    VoxelType  getVoxelType    (const VoxelPos& voxel_coord) const;
    const Voxel&    getVoxel        (const VoxelPos& voxel_coord) const;
    VoxelPos getTopVoxelPos (const VoxelPos& voxel_coord)  const;

    const std::vector<Voxel>& getVoxelDataRef() const;
    const std::vector<Colour>& getColoursRef() const;

    // Setters
    //void setPosition(const BlockPos& position) { m_position = position; }
    
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const Colour&    colour);
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const VoxelType& type  );
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const Voxel&     voxel );

    void updateNeighbours(const VoxelPos& voxel_coord);
    void updateAllNeighbours();

    void changeAllVoxels(const Colour&    colour);
    void changeAllVoxels(const VoxelType& type);
    void changeAllVoxels(const Voxel&     voxel);

    void changeVoxelsFromTo(const Colour&    from_colour, const Colour&    to_colour);
    void changeVoxelsFromTo(const VoxelType& from_type,   const VoxelType& to_type  );
    void changeVoxelsFromTo(const Voxel&     from_voxel,  const Voxel&     to_voxel );

    //Debug
    void printBlock(const bool printVoxels = false) const;


private:

    // Data
    std::vector<Voxel>  m_voxel_data;

    std::vector<Colour> m_block_colours;
    std::queue<ColourID> m_free_colour_ids;

    //BlockManager& mp_manager;
    unsigned int m_block_size;

    //BlockPos   m_position;
    //glm::ivec3 m_dimensions;
    //size_t     m_volume;

    bool m_remesh;
    //bool m_is_empty;

};