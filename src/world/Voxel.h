#pragma once

#include "../pch/pch_std.h"

enum VoxelTypes
{
    Empty = 0,
    Grass,
    Dirt,
    Tree,
    LightSrc,
    Glass,
    Snow ,
    Water,
    Debug,
    Size
};

using ColourID       = uint8_t;
using VoxelType      = uint8_t;
using LightIntensity = uint8_t;

class Voxel
{
private:
    /* 
        Voxel data linearised into 4 bytes
        bits 0-5 : colour id (matches to colour id stored by voxel type in Sector)
        bits 6-11: voxel type (grass/tree/water/stone/etc)
        bit  12  : is voxel empty
        bit  13  : is voxel collidable
        bit  14  : is voxel opaque (for lighting propagation)
        bit  15  : currently spare bit (does voxel have neighbours?)   
        Third byte:  4 bits for sunlight
                     4 bits for red light (i.e. light other than sun)
        Fourth byte: 4 bits for green light
                     4 bits for blue light
    */
    uint32_t data;

public:
    /* 
        Constructors
    */
    Voxel ()                                                      { setType(VoxelTypes::Empty);                  };
    Voxel (const ColourID colour_id, const VoxelTypes voxel_type) { setColourId(colour_id); setType(voxel_type); };

    /* 
        Operators
    */
    bool operator==(const Voxel& other) const { return (data == other.data); }
    bool operator!=(const Voxel& other) const { return !(*this == other); }


    /* 
        Setters
    */
    void setColourId  (const ColourID colour_id)       { data = (data & ~0x3F)      | colour_id;                       } // colour is bits 0-5
    void setType      (const VoxelTypes voxel_type)    { 
        data = (data & ~0xFC0)     | (voxel_type << 6); 
        setFlags(voxel_type);
        } // type is bits 6-11
    void setEmpty     (const bool is_empty)            { is_empty     ? data |= (1 << 12) : data &= ~(1 << 12); } // empty is 12th bit
    void setCollidable(const bool is_colliable)        { is_colliable ? data |= (1 << 13) : data &= ~(1 << 13); } // colliable is 13th bit
    void setOpaque    (const bool is_opaque)           { is_opaque    ? data |= (1 << 14) : data &= ~(1 << 14); } // opaque is 14th bit
    //void setSpare     (bool spare_bit)           { spare_bit    ? data |= (1 << 15) : data &= ~(1 << 15); } // 14th bit is spare bit
    void setSunLight  (const LightIntensity intensity) { data = (data & ~0xF0000)    | (intensity << 16); } // sun light is first nibble for 3rd byte
    void setRedLight  (const LightIntensity intensity) { data = (data & ~0xF00000)   | (intensity << 20); } // red light is second nibble for 3rd byte
    void setGreenLight(const LightIntensity intensity) { data = (data & ~0xF000000)  | (intensity << 24); } // green light is first nibble for 4th byte
    void setBlueLight (const LightIntensity intensity) { data = (data & ~0xF0000000) | (intensity << 28); } // blue light is second nibble for 4th byte

    void setFlags(VoxelType voxel_type)
    {
        //currently switch for readability
        switch (voxel_type) 
        {
            case VoxelTypes::Empty:
                setEmpty(true); setCollidable(false); setOpaque(false);
                break;
            case VoxelTypes::Grass:
                setEmpty(false); setCollidable(false); setOpaque(true);
                break;
            case VoxelTypes::Dirt:
                setEmpty(false); setCollidable(true); setOpaque(true);
                break;
            case VoxelTypes::Tree:
                setEmpty(false); setCollidable(true); setOpaque(true);
                break;
            case VoxelTypes::LightSrc:
                setEmpty(false); setCollidable(false); setOpaque(false);
                break;
            case VoxelTypes::Glass:
                setEmpty(false); setCollidable(true); setOpaque(false);
                break;
            case VoxelTypes::Snow:
                setEmpty(false); setCollidable(false); setOpaque(true);
                break;
            case VoxelTypes::Water:
                setEmpty(false); setCollidable(false); setOpaque(false);
                break;
            case VoxelTypes::Debug:
                setEmpty(false); setCollidable(true); setOpaque(true);
                break;  
            // case VoxelType::Empty:
            //     setEmpty(true); setCollidable(false); setOpaque(true);
            //     break;
        }
    }

    /* 
        Getters
    */

    //uint16_t       getColourHash() const { return data &      0xFFF; }
    const ColourID       getColourId  () const { return data &       0x3F; }
    const VoxelType      getType      () const { return (data &      0xFC0) >> 6; }
    const bool           isEmpty      () const { return data &     0x1000; }
    const bool           isCollidable () const { return data &     0x2000; }
    const bool           isOpaque     () const { return data &     0x4000; }
    //bool           isSpare      () const { return data & 0x8000    ; }
    const LightIntensity getSunLight  () const { return (data &    0xF0000) >> 16; }
    const LightIntensity getRedLight  () const { return (data &   0xF00000) >> 20; }
    const LightIntensity getGreenLight() const { return (data &  0xF000000) >> 24; }
    const LightIntensity getBlueLight () const { return (data & 0xF0000000) >> 28; }


};
    //neighbours |= ( (voxel_coord.x     == 0           ) ? false : (getVoxel({voxel_coord.x - 1, voxel_coord.y    , voxel_coord.z    }).isVisible()) ) << 0;


    /* {
        if (is_empty)
            m_column_info |=  (1 << (block_num + 8));
        else
            m_column_info &= ~(1 << (block_num + 8));
    } */



/* 

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
    bool operator!=(const Voxel& other) const 
    {
        return !(*this == other);
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

    bool hasXMinusNeighbour() const { return (m_neighbours & 0x01); } 
    bool hasXPlusNeighbour()  const { return (m_neighbours & 0x02); } 
    bool hasYMinusNeighbour() const { return (m_neighbours & 0x04); } 
    bool hasYPlusNeighbour()  const { return (m_neighbours & 0x08); } 
    bool hasZMinusNeighbour() const { return (m_neighbours & 0x10); } 
    bool hasZPlusNeighbour()  const { return (m_neighbours & 0x20); } 

    // Debug
    void logVoxel() const { std::cout << "[" << (int)m_colour_id << "," << (int)(m_voxel_type) << "]"; }
}; */