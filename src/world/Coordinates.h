#pragma once

#include "../pch/pch_std.h"

//using ChunkPos = glm::ivec3;
//using BlockPos = glm::uvec3;

using VoxelPos = glm::uvec3;
using BlockPos = glm::uvec3;
using SectorPos = glm::ivec3;

using WorldPos = glm::ivec3;

struct PositionHash 
{
    //Taken from www.github.com/Hopson97/open-builder
    // from Teschner et al., Vision Modeling and Visualization (VMV), 2003
    std::size_t operator()(const glm::uvec3& position) const
    {
        return (position.x * 88339) ^ (position.y * 91967) ^ (position.z * 126323);
    }

    int operator()(const glm::ivec3& position) const
    {
        return (position.x * 88339) ^ (position.y * 91967) ^ (position.z * 126323);
    }
};