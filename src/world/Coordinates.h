#pragma once

#include <glm/vec3.hpp>
#include <utility>
#include <vector>

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
struct VoxelInChunkPos : public Position
{
    using Position::Position;
};*/

struct VoxelInChunkPos
{
    VoxelInChunkPos() {};
    VoxelInChunkPos(const unsigned int& x, const unsigned int& y , const unsigned int& z) : pos({x,y,z}) {};
    VoxelInChunkPos(const glm::uvec3& position) : pos(position) {};
    bool operator==(const VoxelInChunkPos& other) const 
    {
        return ( pos.x == other.pos.x && pos.y == other.pos.y && pos.z == other.pos.z );
    }

    glm::uvec3 pos;
};


struct ChunkPos : public Position 
{
    using Position::Position;
};

struct ChunkPositionHash 
{
    //Taken from www.github.com/Hopson97/open-builder
    // from Teschner et al., Vision Modeling and Visualization (VMV), 2003
    std::size_t operator()(const ChunkPos& position) const
    {
        return (position.pos.x * 88339) ^ (position.pos.y * 91967) ^ (position.pos.z * 126323);
    }
};

typedef std::pair<ChunkPos, VoxelInChunkPos> ChunkAndVoxelPos;
typedef std::pair<ChunkPos, std::vector<VoxelInChunkPos> > ChunkAndManyVoxelPos;