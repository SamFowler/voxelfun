#pragma once

#include "../pch/pch_std.h"

//using BlockColumnInfo = uint32_t;
//1st nibble stores lowest visible block, 2nd nibble stores highest visible block
//2nd byte stores block empty flags, 3rd byte stores block visibility flags
class BlockColumnInfo
{
private:

    //1st nibble stores lowest visible block, 2nd nibble stores highest visible block
    //2nd byte stores block empty flags, 3rd byte stores block visibility flags
    uint32_t m_column_info = 0;
public:
    BlockColumnInfo() : m_column_info(0x00FF07) // sets lowest visible block to 7 and highest visible block to 0, all blocks to empty, and all blocks to not visible
    {};

    bool addBlock(uint8_t block_num)
    {
        setIsBlockEmpty  (block_num, false);
        setIsBlockVisible(block_num, true );//TODO more sophisicated here..take in neighbour blocks and check for their visibility..
        if (block_num < getLowestVisibleBlock())
            setLowestVisibleBlock(block_num);
        if (block_num > getHighestVisibleBlock())
            setHighestVisibleBlock(block_num);

        return isBlockVisible(block_num);
    }

    void setLowestVisibleBlock(uint8_t lowest_visible)
    {
        m_column_info = (m_column_info & ~0xF) | (lowest_visible);
    }

    void setHighestVisibleBlock(uint8_t highest_visible)
    {
        m_column_info = (m_column_info & ~0xF0) | (highest_visible << 4);
    }

    void setIsBlockEmpty(uint8_t block_num, bool is_empty)
    {
        if (is_empty)
            m_column_info |=  (1 << (block_num + 8));
        else
            m_column_info &= ~(1 << (block_num + 8));
    }

    void setIsBlockVisible(uint8_t block_num, bool is_visible)
    {
        if (is_visible)
            m_column_info |=  (1 << (block_num + 16));
        else
            m_column_info &= ~(1 << (block_num + 16));
    }

    unsigned int getLowestVisibleBlock()
    {
        return (m_column_info & 0xF);
    }

    unsigned int getHighestVisibleBlock()
    {
        return ((m_column_info >> 4) & 0xF);
    }

    bool isBlockEmpty(uint8_t block_num)
    {
        return ((m_column_info >> (block_num + 8)) & 1);
    }

    bool isBlockVisible(uint8_t block_num)
    {
        return ((m_column_info >> (block_num + 16)) & 1);
    }

};