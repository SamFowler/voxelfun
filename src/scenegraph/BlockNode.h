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

    void draw(const Uniforms& uniforms)
    {
        vao.getDrawable().bind();

        glUniformMatrix4fv(uniforms.model, 1, GL_FALSE, glm::value_ptr(world_transform)); 
    
        vao.getDrawable().draw();
    }
};