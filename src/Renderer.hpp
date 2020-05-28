#pragma once

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "sdl2_shared.cpp"
#include "Shader.hpp"
#include "VertexArrayObject.hpp"
#include "camera/PerspectiveCameraController.hpp"
#include "camera/OrthographicCameraController.hpp"
#include "Input.hpp" // temp
#include "world/World.hpp"



#include "world/ChunkManager.h"

class Renderer 
{

public:

   // Renderer(int win_width, int win_height, int fov);
    bool init(int win_width, int win_height);

    void clear();
    void draw();
    void tempUpdate(Input& input);

    void destroy();

private:
    std::shared_ptr<SDL_Window> m_window;
    SDL_GLContext m_context;

    PerspectiveCameraController m_perspectiveCameraController = {45, (1280.0f/960.0f), 0.1f, 500.0f};
    //OrthographicCameraController m_ortho_camera_controller = {(1280.0f/960.0f)};

    float last_ticks = 0; //temp

    //temp variables for first shader draw
    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;


    std::vector<VertexArrayObject> m_chunk_vaos;
    ChunkManager m_chunk_manager;



    World m_world;

    Shader m_shader; //TODO: will probably be a map of shaders eventually
    
};