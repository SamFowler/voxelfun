#include "BlockRenderer.h"

#include "BlockMeshGenerator.h"
#include "WireframeMeshGenerator.h"

void BlockRenderer::init()
{


    m_shader.create("cube", "cube");
    m_shader.use();

    uniform_vp = m_shader.getUniformLocation("vp");
    uniform_model = m_shader.getUniformLocation("model");
    //uniform_normalMat = m_shader.getUniformLocation("normal_matrix");

    uniform_lightpos = m_shader.getUniformLocation("lightPos");
    glm::vec3 light_position = {200.0f, 250.0f, 200.0f};
    glUniform3fv(uniform_lightpos, 1, glm::value_ptr(light_position));
    //glUniformMatrixfv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(vp * model));


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



void BlockRenderer::draw(const Camera& camera)
{
    m_shader.use();

    glm::mat4 vp = camera.getProjectionViewMatrix();
    
    //glm::mat4 model(1.0f);
    //glm::mat4 scale = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
    //glm::mat4 scale = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));
    //glm::mat4 normal(0.0f);
    glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));


}

void BlockRenderer::destroy()
{
    m_shader.destroy();
}