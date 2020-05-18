#pragma once

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <memory>
#include <vector>

#include "sdl2_shared.cpp"
#include "Shader.hpp"
#include "VertexArrayObject.hpp"
#include "Camera.hpp"
#include "Input.hpp" // temp

class Renderer 
{

public:


    bool init(int win_width, int win_height);
    void draw();
    void destroy();
    void tempUpdate(Input& input);
private:
    std::shared_ptr<SDL_Window> m_window;
    SDL_GLContext m_context;

    Camera camera;
    float last_ticks = 0; //temp

    //temp variables for first shader draw
    GLint uniform_mvp;

    VertexArrayObject my_cube;
    Shader m_shader; //TODO: will probably be a map of shaders eventually



};