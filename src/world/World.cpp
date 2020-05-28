#include "World.hpp"

//to be moved to world renderer
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //temp, to be moved to world renderer
#include "../Shader.hpp"

void World::init()
{


    //all this init to be moved to a world renderer
    m_shader.create("cube", "cube");
    m_shader.use();

    uniform_vp = m_shader.getUniformLocation("vp");
    uniform_model = m_shader.getUniformLocation("model");
    //uniform_normalMat = m_shader.getUniformLocation("normal_matrix");

    uniform_lightpos = m_shader.getUniformLocation("lightPos");
    glm::vec3 light_position = {10.0f, 5.0f, 10.0f};
    glUniform3fv(uniform_lightpos, 1, glm::value_ptr(light_position));
    //glUniformMatrixfv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(vp * model));
  
    
    m_chunk_manager = ChunkManager(2);
    m_chunk_manager.init();
    
    m_chunk_manager.updateVAOs(m_chunk_vaos);
    std::cout << "updateVAOs size " << m_chunk_vaos.size() << std::endl;
    
}

void World::update(const float& timestep)
{

}


void World::render(const PerspectiveCamera& camera)
{


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


void World::destroy()
{
    m_chunk_manager.destroy();
    //m_world_renderer.destroy();    
}