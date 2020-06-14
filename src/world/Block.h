#pragma once

#include "../pch/pch_std.h"

#include "Voxel.h"
#include "Coordinates.h"
//#include "Colour.h"
#include "WorldConstants.h"

#include "Neighbours.h"

class Block
{
private:
    std::vector<Voxel>  m_voxel_data;
    std::array<Neighbours, BLOCK_VOLUME> m_voxel_neighbours;

public:
    //Constructors
    Block (std::vector<Voxel> voxels);
    
    // Setters
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const VoxelType& type  );
    void setVoxels(const std::vector<VoxelPos>& voxel_coords, const Voxel&     voxel );
    void setVoxel (const VoxelPos& voxel_coord, const Voxel& voxel);

    // Getters
    const Voxel& getVoxel(const VoxelPos& voxel_coord) const { return m_voxel_data[getIndex(voxel_coord)]; }
          Voxel& getVoxel(const VoxelPos& voxel_coord)       { return m_voxel_data[getIndex(voxel_coord)]; }

    const std::vector<Voxel>& getVoxelDataRef() const { return m_voxel_data; } // TODO not sure this is needed

    Neighbours getNeighbours(const VoxelPos& voxel_pos  ) {return m_voxel_neighbours[getIndex(voxel_pos)];}
    Neighbours getNeighbours(const uint32_t& voxel_index) {return m_voxel_neighbours[voxel_index];}
    const Neighbours getNeighbours(const VoxelPos& voxel_pos  ) const {return m_voxel_neighbours[getIndex(voxel_pos)];}
    const Neighbours getNeighbours(const uint32_t& voxel_index) const {return m_voxel_neighbours[voxel_index];}

    // Helpers
    bool isBlockEdge  (const VoxelPos& voxel_coord) const; //TODO not sure this is needed
    bool isBlockEdge  (const uint32_t& voxel_index) const; //TODO not sure this is needed

    void updateNeighbours(const VoxelPos& voxel_coord);
    void updateAllNeighbours();

private:
    uint32_t getIndex   (const VoxelPos& voxel_coord) const;
    VoxelPos getVoxelPos(const uint32_t& index      ) const;
};