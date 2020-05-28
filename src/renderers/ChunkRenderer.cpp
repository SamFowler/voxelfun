#include "ChunkRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ChunkMeshGenerator.h"

#include <iostream>

void ChunkRenderer::init()
{

    m_shader.create("cube", "cube");
    m_shader.use();

    uniform_vp = m_shader.getUniformLocation("vp");
    uniform_model = m_shader.getUniformLocation("model");
    //uniform_normalMat = m_shader.getUniformLocation("normal_matrix");

    uniform_lightpos = m_shader.getUniformLocation("lightPos");
    glm::vec3 light_position = {10.0f, 5.0f, 10.0f};
    glUniform3fv(uniform_lightpos, 1, glm::value_ptr(light_position));
    //glUniformMatrixfv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(vp * model));

}

void ChunkRenderer::getNewChunkUpdates(const std::vector<const Chunk*> updated_chunks)
{

    //if (updated_chunks.size() != 0) 
    //{
        for (auto chunk_ptr : updated_chunks)
        {
            //TODO: check to see if chunk is already on remesh list? 
            m_updated_chunk_list.push_back(chunk_ptr);
        }
    //}
}

void ChunkRenderer::updateVAOs()
{
    for (auto chunk_ptr : m_updated_chunk_list)
    {
        m_chunk_vaos.push_back(ChunkMeshGenerator::makeChunkVAO(*chunk_ptr, 2) );
    }

    //TODO not all meshes may get updated per frame if there are many and it takes time, so don't always clear this list
    m_updated_chunk_list.clear();
}

void ChunkRenderer::draw(const PerspectiveCamera& camera)
{
    std::cout << "drawing chunks" << std::endl;

    m_shader.use();

    glm::mat4 vp = camera.getViewProjection();
    //glm::mat4 vp = m_ortho_camera_controller.getCamera().getProjectionViewMatrix();
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::mat4 model(0.0f);
    glm::mat4 normal(0.0f);
    

    for (auto it = m_chunk_vaos.begin(); it != m_chunk_vaos.end(); ++it)
    {
        it->getDrawable().bind();
        model = glm::translate(glm::mat4(1), glm::vec3(-2.0, -2.0, -2.0) * 8.0f);
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->getDrawable().draw();
    }
}

void ChunkRenderer::destroy()
{
    m_chunk_vaos.clear();
    m_shader.destroy();
}