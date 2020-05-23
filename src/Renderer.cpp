#include "Renderer.hpp"
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

//#include "BlockManager.hpp"
#include "BlockMeshGenerator.hpp"

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

/*
Renderer::Renderer(int win_width, int win_height, int fov)
: m_cameraController(fov, 1.0f*(win_width/win_height))
{
    
}
*/

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

    //SDL_SetWindowFullscreen(m_window.get(), SDL_WINDOW_FULLSCREEN);

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
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(3.0);
    glPointSize(10.0);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Set vsync
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
       std::cout << "Unable to set VSync. SDL error: " << SDL_GetError() << std::endl;
    }

    std::cout << "Renderer successfully initialised with window width " << win_width << " and height " << win_height << std::endl;
    

    m_shader.create("cube", "cube");
    m_shader.use();

    //my_cube = makeIt();


    uniform_vp = m_shader.getUniformLocation("vp");
    uniform_model = m_shader.getUniformLocation("model");
    uniform_normalMat = m_shader.getUniformLocation("normal_matrix");

    uniform_lightpos = m_shader.getUniformLocation("lightPos");
    glm::vec3 light_position = {10.0f, 5.0f, 10.0f};
    glUniform3fv(uniform_lightpos, 1, glm::value_ptr(light_position));
    //glUniformMatrixfv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(vp * model));



    Chunk chunk({2.0f,0.0f,0.0f}, 16);
    chunk.removeVoxel({1,1,1});
    chunk.removeVoxel({2,2,2});
    chunk.removeVoxel({0, 1, 1});
    chunk.makeEfficientChunkMesh();
    m_chunk_renderables.push_back({chunk.getPosition(), chunk.createAndGetVao()});

    
    Chunk chunk2({0.0f,0.0f,0.0f}, {{1.0f, 0.86f, 0.50f}, {0.9f, 0.61f, 0.33f}, {0.39f, 0.83f, 0.74f}}, 8);
    chunk2.removeVoxel({3,3,3});
    chunk2.removeVoxel({5,5,5});
    chunk2.removeVoxel({0, 1, 1});
    chunk2.removeVoxel({0, 1, 2});
    chunk2.removeVoxel({0, 1, 3});
    chunk2.removeVoxel({0, 2, 2});
    chunk2.makeColouredEfficientChunkMesh();
    m_chunk_renderables.push_back({chunk2.getPosition(), chunk2.createAndGetVao()});

    
    Chunk chunk3({0.0f,0.0f,-3.0f}, {{1.0f, 0.86f, 0.50f}, {0.9f, 0.61f, 0.33f}, {0.39f, 0.83f, 0.74f}}, 32);
    chunk3.removeVoxel({10,10,11});
    chunk3.removeVoxel({10,10,12});
    chunk3.removeVoxel({10,10,13});
    chunk3.removeVoxel({10,10,14});
    chunk3.removeVoxel({10,10,15});
    chunk3.removeVoxel({10,10,16});
    chunk3.makeColouredEfficientChunkMesh();
    m_chunk_renderables.push_back({chunk3.getPosition(), chunk3.createAndGetVao()});


    Chunk chunk4({0.0f,0.0f,-2.0f}, {{1.0f, 0.86f, 0.50f}, {0.9f, 0.61f, 0.33f}, {0.39f, 0.83f, 0.74f}}, 32);
    chunk4.removeVoxel({10,1,25});
    chunk4.removeVoxel({10,2,25});
    chunk4.removeVoxel({10,3,25});
    chunk4.removeVoxel({10,4,25});
    chunk4.removeVoxel({10,5,25});
    chunk4.removeVoxel({10,6,25});
    chunk4.makeColouredEfficientChunkMesh();
    m_chunk_renderables.push_back({chunk4.getPosition(), chunk4.createAndGetVao()});


    return true;

}

void Renderer::tempUpdate(Input& input)
{
    float angle = SDL_GetTicks() / 1000.0 * 30; //30deg per second
    glm::vec3 axis_y(0,1,0);
    //glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);

    float ticks = (SDL_GetTicks() / 1000.0);
    float timestep = (last_ticks - ticks);

    m_perspectiveCameraController.update(input, timestep);
    //m_ortho_camera_controller.update(input, timestep);

    m_shader.use();

    last_ticks = ticks;

}

void Renderer::draw() 
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.use();

    glm::mat4 vp = m_perspectiveCameraController.GetCamera().getViewProjection();
    //glm::mat4 vp = m_ortho_camera_controller.getCamera().getProjectionViewMatrix();
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::mat4 model(0.0f);
    glm::mat4 normal(0.0f);
    
    for (auto it = m_chunk_renderables.begin(); it != m_chunk_renderables.end(); ++it)
    {
        model = glm::translate(glm::mat4(1), it->position * 32.0f);
        normal = glm::transpose(glm::inverse(model));
        glUniformMatrix4fv(uniform_normalMat, 1, GL_FALSE, glm::value_ptr(normal));
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->vao.getDrawable().bindAndDraw();
    }
    
    SDL_GL_SwapWindow(m_window.get());
}

void Renderer::destroy()
{
    m_shader.destroy(); // TODO: destroy all shaders when changed to multiple
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}