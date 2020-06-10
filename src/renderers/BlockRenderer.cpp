#include "BlockRenderer.h"

#include "BlockMeshGenerator.h"
#include "WireframeMeshGenerator.h"

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
    glm::vec3 light_position = {200.0f, 250.0f, 200.0f};
    glUniform3fv(uniform_lightpos, 1, glm::value_ptr(light_position));
    //glUniformMatrixfv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(vp * model));


    m_wire_shader.create("wire_cube", "wire_cube");
    m_wire_shader.use();
    wire_uniform_vp = m_wire_shader.getUniformLocation("vp");
    wire_uniform_model = m_wire_shader.getUniformLocation("model");


}
 
/* void BlockRenderer::getNewBlockUpdates(const std::vector<const Block*> updated_blocks)
{
    for (auto block_ptr : updated_blocks)
    {
        //TODO: check to see if block is already on remesh list? 
        m_blocks_to_remesh.push_back(block_ptr);
    }
} */

std::vector<std::pair<const BlockPos, Block&> >& BlockRenderer::getRefToRemeshList()
{
    return m_blocks_to_remesh;
}

void BlockRenderer::addSelectorVAO(WorldPos renderable_pos)
{
    mp_wire_selector_renderable = std::make_unique<WorldRenderable>();
    mp_wire_selector_renderable->position = renderable_pos;
    mp_wire_selector_renderable->vao = WireframeMeshGenerator::makeBlockVAO({255, 0, 255, 0});
}

void BlockRenderer::updateSelectorPosition(const WorldPos& selector_pos)
{
    mp_wire_selector_renderable->position = selector_pos;
}

void BlockRenderer::updateSettings(Input& input)
{
    if (input.wasKeyReleased(SDLK_SLASH))
    {
        if (m_line_mode == false)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            m_line_mode = true;
        } 
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            m_line_mode = false;
        }
    }
}


void BlockRenderer::updateVAOs() 
{
    for (auto block : m_blocks_to_remesh)
    {
        auto it = m_world_renderable_indexes.find(block.first);
        if (it != m_world_renderable_indexes.cend())
        {   
            m_world_renderables[it->second] = {block.first, BlockMeshGenerator::makeBlockVAO(block.second, m_block_size, BlockMeshGenerator::GREEDY_MESH) };
        }
        else
        {
            m_world_renderables.push_back({block.first, BlockMeshGenerator::makeBlockVAO(block.second, m_block_size, BlockMeshGenerator::GREEDY_MESH) });
            m_world_renderable_indexes.emplace(block.first, (m_world_renderables.size() - 1) );
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
    glm::mat4 scale = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
    //glm::mat4 scale = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));
    glm::mat4 normal(0.0f);
    for (auto it = m_world_renderables.begin(); it != m_world_renderables.end(); ++it)
    {   
        it->vao.getDrawable().bind();
        model = glm::translate(scale, glm::vec3(it->position) * m_block_offset);
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->vao.getDrawable().draw();
    }


    m_wire_shader.use();
    mp_wire_selector_renderable->vao.getDrawable().bind();
    model = glm::translate(scale, glm::vec3(mp_wire_selector_renderable->position));
    glUniformMatrix4fv(wire_uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
    glUniformMatrix4fv(wire_uniform_model, 1, GL_FALSE, glm::value_ptr(model));

    mp_wire_selector_renderable->vao.getDrawable().drawWire();

}

void BlockRenderer::destroy()
{
    m_blocks_to_remesh.clear();
    m_world_renderables.clear();
    m_shader.destroy();
}