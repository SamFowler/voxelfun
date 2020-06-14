#pragma once

#include "../pch/pch_std.h"

#include "Voxel.h"
#include "Coordinates.h"
#include "Colour.h"
#include "WorldConstants.h"

#include "Neighbours.h"

class Block
{
public:
    //Constructors
    Block (std::vector<Voxel> voxels);

    // Helpers
    unsigned int    indexFromVoxelPos   (const VoxelPos& voxel_coord) const;
    VoxelPos inBlockPosFromIndex   (const unsigned int&    index      ) const;

    bool isBlockEdge  (const VoxelPos& voxel_coord) const;
    bool isBlockEdge  (const int&             voxel_index) const;

    //ColourID addColour(const Colour& colour);
    //void removeColour (const Colour& colour);
    //void removeColour (const ColourID& colour_id);
    //void removeAllColours();
    //ColourID findColour (const Colour& colour) const;

    // Getters
    // Colour     getColour       (const ColourID&        colour_id  ) const;
    // ColourID   getVoxelColourID(const VoxelPos& voxel_coord) const;
    // Colour     getVoxelColour  (const VoxelPos& voxel_coord) const;
    VoxelType  getVoxelType    (const VoxelPos& voxel_coord) const;
    const Voxel&    getVoxel        (const VoxelPos& voxel_coord) const;
    Voxel&    getVoxel        (const VoxelPos& voxel_coord);
    VoxelPos getTopVoxelPos (const VoxelPos& voxel_coord)  const;

    const std::vector<Voxel>& getVoxelDataRef() const;
    // const std::vector<Colour>& getColoursRef() const;

    // Setters
   
    // void setVoxels(const std::vector<VoxelPos>& voxel_coords, const Colour&    colour);
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const VoxelType& type  );
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const Voxel&     voxel );
    void setVoxel(const VoxelPos& voxel_coord, const Voxel& voxel);


    void updateNeighbours(const VoxelPos& voxel_coord);
    void updateAllNeighbours();

    // void changeAllVoxels(const Colour&    colour);
    void changeAllVoxels(const VoxelType& type);
    void changeAllVoxels(const Voxel&     voxel);

    // void changeVoxelsFromTo(const Colour&    from_colour, const Colour&    to_colour);
    void changeVoxelsFromTo(const VoxelType& from_type,   const VoxelType& to_type  );
    void changeVoxelsFromTo(const Voxel&     from_voxel,  const Voxel&     to_voxel );

    //Debug
    void printBlock(const bool printVoxels = false) const;

    Neighbours getNeighbours(const VoxelPos& voxel_pos  ) {return m_voxel_neighbours[indexFromVoxelPos(voxel_pos)];}
    Neighbours getNeighbours(const uint32_t& voxel_index) {return m_voxel_neighbours[voxel_index];}
    const Neighbours getNeighbours(const VoxelPos& voxel_pos  ) const {return m_voxel_neighbours[indexFromVoxelPos(voxel_pos)];}
    const Neighbours getNeighbours(const uint32_t& voxel_index) const {return m_voxel_neighbours[voxel_index];}

private:

    // Data
    std::vector<Voxel>  m_voxel_data;

    std::array<Neighbours, BLOCK_VOLUME> m_voxel_neighbours;


    //std::vector<Colour> m_block_colours;
    //std::queue<ColourID> m_free_colour_ids;

    //std::unordered_map<ColourID, Colour> m_colours;

};