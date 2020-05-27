#include "Renderer.hpp"
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

#include "BlockMeshGenerator.hpp"
//#include "BChunk.hpp"
#include "BlockMeshManager.hpp"
#include "DefaultBlockMaker.hpp"

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


    int block_size = 8;

    m_block_manager = BlockManager(block_size);

    //BlockManager block_manager(block_size);
    BlockMeshManager mesh_manager;
        
    //Mesh mesh = BlockMeshGenerator::makeBlockMesh(*block_manager.getBlock(block_id), CULL_MESH_FAST);
    //mesh_manager.addMesh(BlockMeshGenerator::makeBlockMesh(*block_manager.getBlock(block_id), CULL_MESH_FAST));
   
    m_block_manager.addBlock(DefaultBlockMaker::makeBlock(block_size, GRASS_ONE));
    m_block_manager.addBlock(DefaultBlockMaker::makeBlock(block_size, GRASS_TWO));
    m_block_manager.addBlock(DefaultBlockMaker::makeBlock(block_size, DIRT_ONE));   
    m_block_manager.addBlock(DefaultBlockMaker::makeBlock(block_size, PLACEHOLDER));

    //Mesh mesh = BlockMeshGenerator::makeBlockMesh(*block_manager.getBlock(block_id), CULL_MESH_FAST);
    //mesh_manager.addMesh(BlockMeshGenerator::makeBlockMesh(*block_manager.getBlock(block_id), CULL_MESH_FAST));



    // MAKE CHUNK FROM BLOCKS
    
    std::vector<BlockID> blocks(block_size*block_size*block_size, 1);
    for (int i = 0; i < block_size*block_size*block_size; i++) {
        if (rand()% 50 == 0) 
            blocks[i] = 0;
        if ((rand() % 20) == 0)
            blocks[i] = 2;
    }

    BChunk bchunk();
    //Mesh chunk_mesh = bchunk.makeMesh(mesh_manager);
    //Mesh chunk_mesh = bchunk.makeMesh(block_manager);

    m_world.addChunk( { block_size, {0.0f, -1.0f, 1.0f}, blocks } );
    m_world.addChunk( { block_size, {1.0f, -1.0f, 1.0f}, blocks } );

    //blocks.clear();
    for (int i = 0; i < block_size*block_size*block_size; i++) {
        
        if (rand()% 10 == 0) 
            blocks[i] = 3;
        if ((rand() % 10) == 0)
            blocks[i] = 2;
        if ((rand() % 10) == 0)
            blocks[i] = 4;
        else
            blocks[i] = 1;
    }

    m_world.addChunk( { block_size, {0.0f, -1.0f, 2.0f}, blocks } );
    m_world.addChunk( { block_size, {1.0f, -1.0f, 2.0f}, blocks } );
    



    m_chunk_render_list = m_world.getWorldRenderList();
    //m_block_render_list = bchunk.getBlockRenderList();
     
    //const Block* block_ptr = block_manager.getBlock(1);
    //Mesh mesh = BlockMeshGenerator::makeBlockMesh(*block_ptr, CULL_MESH_FAST);
    //std::shared_ptr<VertexArrayObject> ptr = std::make_shared<VertexArrayObject>(mesh.createBuffer());

    //block_ptr = block_manager.getBlock(2);
    //mesh = BlockMeshGenerator::makeBlockMesh(*block_ptr, CULL_MESH_FAST);
    //std::shared_ptr<VertexArrayObject> ptr2 = std::make_shared<VertexArrayObject>(mesh.createBuffer());


    m_block_manager.updateDrawables(m_block_drawables);
    
    

    m_chunk_manager = ChunkManager(2);
    m_chunk_manager.init();
    
    m_chunk_manager.updateVAOs(m_chunk_vaos);
    std::cout << "updateVAOs size " << m_chunk_vaos.size() << std::endl;


    //m_block_drawables.push_back(block_manager.getDrawableVAO(1));
    //m_block_drawables.push_back(block_manager.getDrawableVAO(2));
    //std::shared_ptr<VertexArrayObject> ptr = std::make_shared<VertexArrayObject>(mesh.createBuffer());

    //m_chunk_renderables.push_back({glm::vec3(1.0f, -1.0f, 1.0f), ptr});
    /*
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            m_chunk_renderables.push_back({glm::vec3(i, -1.0f, j), ptr});
        }
    }

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if ( (rand() % 5) == 0)
                m_chunk_renderables.push_back({glm::vec3(i, 0.0f, j), ptr2});
        }
    }
 */

    

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
    

    for (auto it = m_chunk_vaos.begin(); it != m_chunk_vaos.end(); ++it)
    {
        it->getDrawable().bind();
        model = glm::translate(glm::mat4(1), glm::vec3(-2.0, -2.0, -2.0) * 8.0f);
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->getDrawable().draw();
    }

    for (auto block_rl : m_chunk_render_list)
    {
        for (auto it : *block_rl)
        {
            
        
            BlockID block_id = it.first;
            DrawableVAO drawable = m_block_drawables[block_id].getDrawable();
            //DrawableVAO drawable = m_block_manager.getDrawableVAO(block_id);
            drawable.bind();
            
            std::vector<glm::ivec3> vec = it.second;
            for (auto vec_it : vec)
            {
                
                model = glm::translate(glm::mat4(1), glm::vec3(vec_it) * 8.0f);
                glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
                glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

                drawable.draw();
            
            }

        }
    }

    /*
    for (auto it = m_chunk_renderables.begin(); it != m_chunk_renderables.end(); ++it)
    {
        //model = glm::scale(glm::mat4(1), {0.1f, 0.1f, 0.1f}) * glm::translate(glm::mat4(1), it->position * 8.0f);
        model = glm::translate(glm::mat4(1), it->position * 8.0f);

        //normal = glm::transpose(glm::inverse(model));
        //glUniformMatrix4fv(uniform_normalMat, 1, GL_FALSE, glm::value_ptr(normal));
        glUniformMatrix4fv(uniform_vp, 1, GL_FALSE, glm::value_ptr(vp));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        it->vao->getDrawable().bindAndDraw();
    }
    */
    
    SDL_GL_SwapWindow(m_window.get());
}

void Renderer::destroy()
{
    m_shader.destroy(); // TODO: destroy all shaders when changed to multiple
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}