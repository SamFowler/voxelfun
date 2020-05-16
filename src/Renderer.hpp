#pragma once
#include <GL/glew.h>
//#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <memory>
#include "sdl2_shared.cpp"


class Renderer {

public:
    bool Init(int win_width, int win_height);
    void Draw();

private:
    std::shared_ptr<SDL_Window> m_window;


};