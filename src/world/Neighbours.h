#pragma once

#include "../pch/pch_std.h"

class Neighbours
{

private:
    uint8_t m_neighbours;

public:    

    /*
        neighbour position vs xyz
        (0 means neighbour in negative direction, 1 in positive direction) 
        zero bit: x-minus neighbour
         1st bit: x-plus  neighbour
         2nd bit: y-minus neighbour
         3rd bit: y-plus neighbour
         4th bit: z-minus neighbour
         5th bit: z-plus neighbour

        #: 0 1 2 3 4 5
        --------------
        x: 0 1 0 1 0 1
        y: 0 0 0 0 1 1
        z: 0 0 1 1 0 0
    */
    //Neighbours() {m_neighbours = 0x00;}

    uint8_t   getNeighbours() const { return m_neighbours; }
    void setNeighbours(const uint8_t& neighbours) { m_neighbours = neighbours; }

    void setXMinus(bool neighbour_exists) { setNeighbour(0, neighbour_exists); }
    void setXPlus (bool neighbour_exists) { setNeighbour(1, neighbour_exists); }
    void setYMinus(bool neighbour_exists) { setNeighbour(2, neighbour_exists); }
    void setYPlus (bool neighbour_exists) { setNeighbour(3, neighbour_exists); }
    void setZMinus(bool neighbour_exists) { setNeighbour(4, neighbour_exists); }
    void setZPlus (bool neighbour_exists) { setNeighbour(5, neighbour_exists); }

    bool xMinusExists() const { return (m_neighbours & 0x01); } 
    bool xPlusExists () const { return (m_neighbours & 0x02); } 
    bool yMinusExists() const { return (m_neighbours & 0x04); } 
    bool yPlusExists () const { return (m_neighbours & 0x08); } 
    bool zMinusExists() const { return (m_neighbours & 0x10); } 
    bool zPlusExists () const { return (m_neighbours & 0x20); } 

private:
    void setNeighbour(const uint8_t& neighbour_position, const bool neighbour_exists) {
        neighbour_exists   ?   m_neighbours |= (1 << neighbour_position)   :   m_neighbours &= ~(1 << neighbour_position);
    }

};