#pragma once

#include <cstdint>
#include <iostream> //debug TODO replace with log

enum class VoxelType : uint8_t 
{
    Empty = 0,
    Grass = 1,
    Dirt  = 2,
};

using ColourID = uint8_t;

class Voxel
{
private:
    // Voxel data
    ColourID  m_colour_id;
    VoxelType m_voxel_type;
    uint8_t   m_neighbours;
    uint8_t   m_light;

public:
    // Constructors
    Voxel ()                                                         
        : m_colour_id(0), m_voxel_type(VoxelType::Empty), m_neighbours(0), m_light(0) {};

    Voxel ( const ColourID& colour_id, const VoxelType& voxel_type ) 
        : m_colour_id(colour_id), m_voxel_type(voxel_type), m_neighbours(0), m_light(0) {};

    bool operator==(const Voxel& other) const 
    {
        return ( m_colour_id == other.m_colour_id && m_voxel_type == other.m_voxel_type);
    }

    // Getters
    ColourID  getColourId()   const { return m_colour_id;  }
    VoxelType getType()       const { return m_voxel_type; }
    uint8_t   getNeighbours() const { return m_neighbours; }

    // Setters
    void setColourId  (const ColourID&  colour_id)  { m_colour_id = colour_id;  }
    void setType      (const VoxelType& voxel_type) { m_voxel_type = voxel_type; }
    void setNeighbours(const uint8_t&   neighbours) { m_neighbours = neighbours; }

    // Utility
    bool isVisible()      const  { return ( m_voxel_type != VoxelType::Empty ); }
    bool isOccupiable()   const  { return ( m_voxel_type == VoxelType::Empty ); }
    bool isDestructable() const  { return isVisible(); }

    bool hasXMinusNeighbour() const { return m_neighbours && 0x01; } 
    bool hasXPlusNeighbour()  const { return m_neighbours && 0x02; } 
    bool hasYMinusNeighbour() const { return m_neighbours && 0x04; } 
    bool hasYPlusNeighbour()  const { return m_neighbours && 0x08; } 
    bool hasZMinusNeighbour() const { return m_neighbours && 0x10; } 
    bool hasZPlusNeighbour()  const { return m_neighbours && 0x20; } 

    // Debug
    void logVoxel() const { std::cout << "[" << (int)m_colour_id << "," << (int)(m_voxel_type) << "]"; }
};