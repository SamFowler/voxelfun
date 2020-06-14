#pragma once

#include "../pch/pch_std.h"

enum VoxelTypes
{
    Empty = 0,
    Grass = 1,
    Dirt  = 2,
    Tree  = 3,
    LightSrc = 4,
    Debug = 5,
    Size
};

using ColourID = uint8_t;
using MaterialID = uint16_t;
using VoxelType = uint8_t;

class Voxel
{
private:
    // Voxel data
    ColourID  m_colour_id;
    VoxelType m_voxel_type;
    uint8_t   m_light;

public:
    // Constructors
    Voxel ()                                                         
        : m_colour_id(0), m_voxel_type(VoxelTypes::Empty), m_light(0) {};

    Voxel ( const ColourID& colour_id, const VoxelTypes& voxel_type ) 
        : m_colour_id(colour_id), m_voxel_type(voxel_type), m_light(0) {};

    bool operator==(const Voxel& other) const 
    {
        return ( m_colour_id == other.m_colour_id && m_voxel_type == other.m_voxel_type);
    }
    bool operator!=(const Voxel& other) const 
    {
        return !(*this == other);
    }

    // Getters
    ColourID  getColourId()   const { return m_colour_id;  }
    VoxelType getType()       const { return m_voxel_type; }

    // Setters
    void setColourId  (const ColourID&  colour_id)  { m_colour_id = colour_id;  }
    void setType      (const VoxelType& voxel_type) { m_voxel_type = voxel_type; }

    // Utility
    bool isVisible()      const  { return ( m_voxel_type != VoxelTypes::Empty ); }
    bool isOccupiable()   const  { return ( m_voxel_type == VoxelTypes::Empty ); }
    bool isDestructable() const  { return isVisible(); }

    // Debug
    void logVoxel() const { std::cout << "[" << (int)m_colour_id << "," << (int)(m_voxel_type) << "]"; }
};