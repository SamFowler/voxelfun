#pragma once

#include "../pch/pch_std.h"

#include "Node.h"
#include "../opengl_api/VertexArrayObject.h"

class BlockNode : public Node
{
private:
    glm::mat4 world_transform;
    DrawableVAO vao;
public:
    void draw(const Uniforms& uniforms)
    {

        vao.bind();
        //model = glm::translate(scale, glm::vec3(it->position) * (float)BLOCK_SIZE);
        glUniformMatrix4fv(uniforms.model, 1, GL_FALSE, glm::value_ptr(world_transform)); 
        

        vao.draw();
    }
};