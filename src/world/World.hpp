#pragma once

#include "../Input.hpp"

#include "../camera/PerspectiveCamera.hpp"
#include "ChunkManager.h"
#include "../renderers/ChunkRenderer.h"

#include <vector>
#include <memory>

#include "../opengl_api/Shader.hpp" // temp, to be moved to world renderer

class World
{
public:
    void init();
    void update(const float& timestep);
    void render(const PerspectiveCamera& camera);
   
    void destroy();

private:

    ChunkManager m_chunk_manager;
    ChunkRenderer m_chunk_renderer;
 
    //temp, to be moved to a world renderer
//    WorldRenderer m_world_renderer;
    std::vector<VertexArrayObject> m_chunk_vaos;
    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;
    Shader m_shader;


};