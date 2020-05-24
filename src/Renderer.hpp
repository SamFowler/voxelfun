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
#include "PerspectiveCameraController.hpp"
#include "OrthographicCameraController.hpp"
#include "Input.hpp" // temp
#include "Chunk.hpp"
#include "Block.hpp"
#include "BlockManager.hpp"
#include "BChunk.hpp"
#include "World.hpp"

class Renderer 
{

public:

   // Renderer(int win_width, int win_height, int fov);
    bool init(int win_width, int win_height);
    void draw();
    void destroy();
    void tempUpdate(Input& input);
private:
    std::shared_ptr<SDL_Window> m_window;
    SDL_GLContext m_context;

    PerspectiveCameraController m_perspectiveCameraController = {45, (1280.0f/960.0f), 0.1f, 500.0f};
    OrthographicCameraController m_ortho_camera_controller = {(1280.0f/960.0f)};

    float last_ticks = 0; //temp

    //temp variables for first shader draw
    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;

    std::vector<Chunk> m_chunks;
    std::vector<Renderable> m_chunk_renderables;
    std::unordered_map<BlockID, VertexArrayObject> m_block_drawables;

    BlockRenderList m_block_render_list;
    std::vector<BlockRenderList*> m_chunk_render_list;

    BlockManager m_block_manager;

    World m_world;
    //std::vector<std::shared_ptr<VertexArrayObject>> m_vaos;
    Shader m_shader; //TODO: will probably be a map of shaders eventually
    
};