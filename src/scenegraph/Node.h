#pragma once

#include "../pch/pch_std.h"

#include "../opengl_api/UniformPasser.h"
#include "../world/Coordinates.h"

class BlockNode;

class Node
{
protected:
    glm::uvec3 m_origin;
    glm::uvec3 m_half_size;

    bool m_is_leaf;

public:
    virtual void draw(const Uniforms& uniforms) = 0;

    virtual void addBlock(const BlockPos& pos, BlockNode& node) {};
    virtual void deleteBlock(const BlockPos& pos) {};
    virtual bool isEmpty() {return false;};
    
};