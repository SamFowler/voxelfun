#pragma once

//#include <glm/vec3.hpp>
//#include <utility>
//#include <vector>

#include "../pch/pch_std.h"

struct Position
{
    Position() {};
    Position(const int& x, const int& y , const int& z) : pos({x,y,z}) {};
    Position(const glm::ivec3& position) : pos(position) {};
    bool operator==(const Position& other) const 
    {
        return ( pos.x == other.pos.x && pos.y == other.pos.y && pos.z == other.pos.z );
    }

    glm::ivec3 pos;
};

struct VoxelWorldPos : public Position
{
    using Position::Position;
};
/*
struct VoxelInBlockPos : public Position
{
    using Position::Position;
};*/

struct VoxelInBlockPos
{
    VoxelInBlockPos() {};
    VoxelInBlockPos(const unsigned int& x, const unsigned int& y , const unsigned int& z) : pos({x,y,z}) {};
    VoxelInBlockPos(const glm::uvec3& position) : pos(position) {};
    bool operator==(const VoxelInBlockPos& other) const 
    {
        return ( pos.x == other.pos.x && pos.y == other.pos.y && pos.z == other.pos.z );
    }

    glm::uvec3 pos;
};


struct BlockPos : public Position 
{
    using Position::Position;
};

struct BlockPositionHash 
{
    //Taken from www.github.com/Hopson97/open-builder
    // from Teschner et al., Vision Modeling and Visualization (VMV), 2003
    std::size_t operator()(const BlockPos& position) const
    {
        return (position.pos.x * 88339) ^ (position.pos.y * 91967) ^ (position.pos.z * 126323);
    }
};

typedef std::pair<BlockPos, VoxelInBlockPos> BlockAndVoxelPos;
typedef std::pair<BlockPos, std::vector<VoxelInBlockPos> > BlockAndManyVoxelPos;