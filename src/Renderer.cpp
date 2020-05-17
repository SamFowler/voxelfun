#include "Renderer.hpp"
#include <iostream>
#include <fstream>

bool Renderer::Init(int win_width = 640, int win_height = 480) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL could not initialise. SDL_Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    m_window = sdl_shared(SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            win_width, win_height,
            SDL_WINDOW_SHOWN |
            SDL_WINDOW_OPENGL |
            SDL_WINDOW_RESIZABLE
            ));

    if (m_window == nullptr) {
        std::cout << "Could not create window. SDL error: " << SDL_GetError() << std::endl;
        return 0;
    }

    glEnable(GL_MULTISAMPLE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    
    m_context = SDL_GL_CreateContext(m_window.get());

    if (m_context == NULL) {
        std::cout << "OpenGL context could not be created. SDL error: " << SDL_GetError() << std::endl;
    }

    //Initialise GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cout << "Glew could not be initialised. Glew error: " << glewGetErrorString(glewError) << std::endl;
    }

    std::cout << "Renderer successfully initialised with window width " << win_width << " and height " << win_height << std::endl;


    //Set vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
       std::cout << "Unable to set VSync. SDL error: " << SDL_GetError() << std::endl;
    }

    
    
    
    //Vertex Array Object to store links between attributes and VBOs
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Vertex Buffer Object to send vertex data to GPU
    glGenBuffers(1, &m_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), m_positions, GL_STATIC_DRAW); //6 because positions is triangle at the moment

    //unsigned int shaderProgram = CreateShader("shaders/cube_vert.glsl", "shaders/cube_frag.glsl");
    m_shader.Create("cube", "cube");
    m_shader.Use();
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);


    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;

}

void Renderer::Draw() 
{
    glClear(GL_COLOR_BUFFER_BIT);


    glDrawArrays(GL_TRIANGLES, 0, 3);
    

    SDL_GL_SwapWindow(m_window.get());
}

void Renderer::Destroy()
{
    m_shader.Destroy(); // TODO: destroy all shaders when changed to multiple
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}