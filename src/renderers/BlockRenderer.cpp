#include "BlockRenderer.h"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>

#include "../pch/pch_std.h"


#include "BlockMeshGenerator.h"

#include "../helpers/Logging.h"

void BlockRenderer::init(const unsigned int& block_size)
{
    m_block_offset = (float)block_size;
    m_block_size = block_size;


    m_shader.create("cube", "cube");
    m_shader.use();

    uniform_vp = m_shader.getUniformLocation("vp");
    uniform_model = m_shader.getUniformLocation("model");
    //uniform_normalMat = m_shader.getUniformLocation("normal_matrix");

    uniform_lightpos = m_shader.getUniformLocation("lightPos");
    glm::vec3 light_position = {10.0f, 15.0f, 10.0f};
    glUniform3fv(uniform_lightpos, 1, glm::value_ptr(light_position));
    //glUniformMatrixfv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(vp * model));

}

void BlockRenderer::getNewBlockUpdates(const std::vector<const Block*> updated_blocks)
{

    //if (updated_blocks.size() != 0) 
    //{
        for (auto block_ptr : updated_blocks)
        {
            //TODO: check to see if block is already on remesh list? 
            m_updated_block_list.push_back(block_ptr);
        }
    //}
}

void BlockRenderer::updateVAOs()
{
    for (auto block_ptr : m_updated_block_list)
    {
        if (block_ptr != nullptr)
        {
            //m_block_vaos.push_back(BlockMeshGenerator::makeBlockVAO(*block_ptr, block_size) );
            m_block_renderables.push_back({block_ptr->getPosition(), BlockMeshGenerator::makeBlockVAO(*block_ptr, m_block_size, BlockMeshGenerator::GREEDY_MESH) });
        }
    }

    //TODO not all meshes may get updated per frame if there are many and it takes time, so don't always clear this list
    m_updated_block_list.clear();
}

//void BlockRenderer::draw(const PerspectiveCamera& camera)
void BlockRenderer::draw(const Camera& camera)
{
    m_shader.use();

    glm::mat4 vp = camera.getProjectionViewMatrix();
    //glm::mat4 vp = m_ortho_camera_controller.getCamera().getProjectionViewMatrix();
    
    glm::mat4 model(1.0f);
    glm::mat4 scale = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
    glm::mat4 normal(0.0f);
    for (auto it = m_block_renderables.begin(); it != m_block_renderables.end(); ++it)
    {   
        it->vao.getDrawable().bind();
        model = glm::translate(scale, glm::vec3(it->position.pos) * m_block_offset);
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->vao.getDrawable().draw();
    }
}

void BlockRenderer::destroy()
{
    m_updated_block_list.clear();
    m_block_vaos.clear();
    m_shader.destroy();
}