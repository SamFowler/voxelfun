#pragma once

#include "../pch/pch_std.h"

#include "Node.h"
#include "../opengl_api/VertexArrayObject.h"

class BlockNode : public Node
{
private:
    glm::mat4 world_transform;
    VertexArrayObject vao;
public:
    BlockNode(const glm::mat4& transform, VertexArrayObject&& drawable) : world_transform(transform), vao(std::move(drawable)) {};

    void draw(const Frustum& frustum, const Uniforms& uniforms, uint32_t& num_draws)
    {
        WorldPos world_pos = CoordinateConversion::getWorldPos({0,0,0}, m_origin); // TODO just store world position within node

        if (!frustum.cubeInFrustum(world_pos, world_pos+BLOCK_SIZE))
            return;

        vao.getDrawable().bind();

        glUniformMatrix4fv(uniforms.model, 1, GL_FALSE, glm::value_ptr(world_transform)); 
    
        vao.getDrawable().draw();
        num_draws++;
    }
};