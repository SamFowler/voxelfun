#include "BlockRenderer.h"

#include "BlockMeshGenerator.h"
 
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
 
/* void BlockRenderer::getNewBlockUpdates(const std::vector<const Block*> updated_blocks)
{
    for (auto block_ptr : updated_blocks)
    {
        //TODO: check to see if block is already on remesh list? 
        m_blocks_to_remesh.push_back(block_ptr);
    }
} */

std::vector<std::pair<const BlockPos, const Block*> >& BlockRenderer::getRefToRemeshList()
{
    return m_blocks_to_remesh;
}

void BlockRenderer::updateVAOs() 
{
    for (auto block_ptr : m_blocks_to_remesh)
    {
        if (block_ptr.second != nullptr)
        {
            m_block_renderables.push_back({block_ptr.first, BlockMeshGenerator::makeBlockVAO(*block_ptr.second, m_block_size, BlockMeshGenerator::GREEDY_MESH) });
        }
    }

    //TODO not all meshes may get updated per frame if there are many and it takes time, so don't always clear this list
    m_blocks_to_remesh.clear();
}

void BlockRenderer::draw(const Camera& camera)
{
    m_shader.use();

    glm::mat4 vp = camera.getProjectionViewMatrix();
    
    glm::mat4 model(1.0f);
    //glm::mat4 scale = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
    glm::mat4 scale = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
    glm::mat4 normal(0.0f);
    for (auto it = m_block_renderables.begin(); it != m_block_renderables.end(); ++it)
    {   
        it->vao.getDrawable().bind();
        model = glm::translate(scale, glm::vec3(it->position) * m_block_offset);
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->vao.getDrawable().draw();
    }
}

void BlockRenderer::destroy()
{
    m_blocks_to_remesh.clear();
    m_block_renderables.clear();
    m_shader.destroy();
}