#include "Renderer.hpp"
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
            SDL_WINDOW_OPENGL
            //| SDL_WINDOW_RESIZABLE
            ));

    if (m_window == nullptr) {
        std::cout << "Could not create window. SDL error: " << SDL_GetError() << std::endl;
        return 0;
    }

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

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    //glGenBuffers(1, &m_buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    //glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), m_positions, GL_STATIC_DRAW); //6 because positions is triangle at the moment

    //Send cube model data to GPU
    //send vertices
    glGenBuffers(1, &m_vbo_cube_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_vertices), m_cube_vertices, GL_STATIC_DRAW);
    //send colours
    glGenBuffers(1, &m_vbo_cube_colours);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_cube_colours);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_cube_colours), m_cube_colours, GL_STATIC_DRAW);
    //send vertices element information
    glGenBuffers(1, &m_ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_cube_elements), m_cube_elements, GL_STATIC_DRAW);

    



    //unsigned int shaderProgram = CreateShader("shaders/cube_vert.glsl", "shaders/cube_frag.glsl");
    m_shader.Create("cube", "cube");
    m_shader.Use();
    
    attribute_coord3d = m_shader.GetAttributeLocation("coord3d");
    attribute_v_colour = m_shader.GetAttributeLocation("v_colour");
    uniform_mvp = m_shader.GetUniformLocation("mvp");

    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    //glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
    //int size;
    //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    //glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);


    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;

}

void Renderer::TempUpdate()
{
    float angle = SDL_GetTicks() / 1000.0 * 45; //45deg per second
    glm::vec3 axis_y(0,1,0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);
    
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(45.0f, 1.0f*640/480, 0.1f, 10.f);

    glm::mat4 mvp = projection * view * model * anim;

    m_shader.Use();
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Renderer::Draw() 
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.Use();

    glEnableVertexAttribArray(attribute_coord3d);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_cube_vertices);
    glVertexAttribPointer(
        attribute_coord3d,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );

    glEnableVertexAttribArray(attribute_v_colour);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_cube_colours);
    glVertexAttribPointer(
        attribute_v_colour,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_cube_elements);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(attribute_coord3d);
    glDisableVertexAttribArray(attribute_v_colour);
    //int size;
    //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    //glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 4);
    

    SDL_GL_SwapWindow(m_window.get());
}

void Renderer::Destroy()
{
    m_shader.Destroy(); // TODO: destroy all shaders when changed to multiple
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}