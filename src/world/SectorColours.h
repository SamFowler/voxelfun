#pragma once

#include "../pch/pch_std.h"

#include "Colour.h"
#include "Voxel.h"

class SectorColours
{
private:
    
    std::vector< std::vector< Colour> > m_colours;

    //pair for each voxel type holding whether there is a cleared colour id to be filled, or if not the max colour id to use
    std::vector<std::queue<ColourID> > m_next_colour_ids;


public:
    SectorColours()
    {
        m_colours.resize(VoxelTypes::Size);
        m_next_colour_ids.resize(VoxelTypes::Size);

        addColour(VoxelTypes::Empty, {0, 0, 0, 0});
        addColour(VoxelTypes::Debug, {255, 0, 255, 255});
    }

    ColourID addColour(const VoxelTypes& voxel_type, const Colour& colour) 
    {   
        std::queue<ColourID> next_ids = m_next_colour_ids[voxel_type];

        if ( next_ids.empty() )
        {
            m_colours[voxel_type].push_back(colour);
            return ( m_colours[voxel_type].size() - 1 );
        }
        else
        {
            ColourID id = next_ids.front();
            m_colours[voxel_type][id] = colour;
            next_ids.pop();
            return id;
        }
    }

    void changeColour(const Voxel& voxel, const Colour& colour)
    {
        // TODO need to do bounds checking?
        //if (inBounds(voxel))
            m_colours[voxel.getType()][voxel.getColourId()] = colour;
    }

    void removeColour(const Voxel& voxel)
    {
        m_colours[voxel.getType()][voxel.getColourId()] = {0,0,0,0};
        m_next_colour_ids[voxel.getType()].push(voxel.getColourId());
    }

    //Colour getColour(const uint16_t type_colour_hash) { return m_colours[type_colour_hash]; }
    Colour getColour(const Voxel& voxel) const
    {
        return m_colours[voxel.getType()][voxel.getColourId()];
    }

private:
    bool inBounds(const Voxel& voxel) const
    {
        if (voxel.getType() < m_colours.size() )
            if ( voxel.getColourId() < m_colours[voxel.getType()].size() )
                return true;
        
        return false;
    }

};
