#pragma once

#include "../pch/pch_std.h"

#include "../opengl_api/UniformPasser.h"
#include "../world/Coordinates.h"

#include "../renderers/Frustum.h"
#include "../world/WorldConstants.h"

class BlockNode;

class Node
{
protected:
    glm::uvec3 m_origin;
    glm::uvec3 m_half_size;

public:
    virtual void draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws) = 0;

    void setOrigin(const glm::uvec3 origin) {m_origin = origin;}

    virtual void addBlock(const BlockPos& pos, BlockNode& node) {};
    virtual void deleteBlock(const BlockPos& pos) {};
    virtual bool isEmpty() {return false;};
    
};