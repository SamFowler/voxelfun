#include "Renderer.hpp"
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

VertexArrayObject makeIt()
{

    std::vector<GLfloat> verts = {
        //front
        -0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
         0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,

        //back
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

     std::vector<GLfloat> colours = {
        //front colours
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        //back colours
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    std::vector<GLuint> elements = {
        //front
        0, 1, 2,
        2, 3, 0,
        //right
        1, 5, 6,
        6, 2, 1,
        //back 
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        //bottom
        4, 5, 1,
        1, 0, 4,
        //top
        3, 2, 6,
        6, 7, 3,
    };

    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, verts);
    vao.addVertexBuffer(3, colours);
    vao.addElementBuffer(elements);
    return vao;
}


bool Renderer::init(int win_width = 640, int win_height = 480)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
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

    if (m_window == nullptr)
    {
        std::cout << "Could not create window. SDL error: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    
    m_context = SDL_GL_CreateContext(m_window.get());

    if (m_context == NULL)
    {
        std::cout << "OpenGL context could not be created. SDL error: " << SDL_GetError() << std::endl;
    }

    //Initialise GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cout << "Glew could not be initialised. Glew error: " << glewGetErrorString(glewError) << std::endl;
    }

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Set vsync
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
       std::cout << "Unable to set VSync. SDL error: " << SDL_GetError() << std::endl;
    }

    std::cout << "Renderer successfully initialised with window width " << win_width << " and height " << win_height << std::endl;
    
    camera.init();


    m_shader.create("cube", "cube");
    m_shader.use();

    my_cube = makeIt();

    uniform_mvp = m_shader.getUniformLocation("mvp");



    return true;

}

void Renderer::tempUpdate(Input& input)
{
    float angle = SDL_GetTicks() / 1000.0 * 0; //45deg per second
    glm::vec3 axis_y(0,1,0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);
    
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));


    const float radius = 10.0f;
    float x = sin(SDL_GetTicks()/1000.0) * radius;
    float z = cos(SDL_GetTicks()/1000.0) * radius;
    float ticks = (SDL_GetTicks() / 1000.0);

    float move_amount = (last_ticks - ticks)* 5;
    glm::vec3 move_vec(0.0);
  
    if (input.isKeyHeld(SDLK_s)) 
    {
        camera.moveForward(move_amount);
    }
    else if (input.isKeyHeld(SDLK_w)) 
    {   
        camera.moveForward(-move_amount);
    }
    if (input.isKeyHeld(SDLK_a)) 
    {   
        camera.moveSideways(move_amount);
    }
    else if (input.isKeyHeld(SDLK_d)) 
    {   
        camera.moveSideways(-move_amount);
    }
    if (input.isKeyHeld(SDLK_f)) 
    {   
        move_vec.z -= move_amount;
    }
    else if (input.isKeyHeld(SDLK_r)) 
    {   
        move_vec.z += move_amount;
    }
    //std::cout << "move amount = " << move_vec.x << "," << move_vec.y << "," << move_vec.z << std::endl;
    camera.move(move_vec);


    const float sensitivity = 0.15f;
    glm::ivec2 rel_pos = input.getRelMousePos();
    glm::vec2 rel_change = glm::vec2((rel_pos.x * sensitivity), (rel_pos.y * sensitivity));
    std::cout << "rm_x:" << rel_change.x << " rm_y:" << rel_change.y << std::endl;
    

    camera.changeYaw(rel_change.x);
    camera.changePitch(rel_change.y);
    
    camera.updateDirection();
    
    glm::mat4 view = camera.getView();

    glm::mat4 projection = glm::perspective(45.0f, 1.0f*640/480, 0.1f, 100.f);
    //glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -10.0f, 10.0f);
    glm::mat4 mvp = projection * view * model * anim;

    m_shader.use();
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    last_ticks = ticks;

}

void Renderer::draw() 
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.use();

    my_cube.getDrawable().bindAndDraw();

    SDL_GL_SwapWindow(m_window.get());
}

void Renderer::destroy()
{
    m_shader.destroy(); // TODO: destroy all shaders when changed to multiple
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}