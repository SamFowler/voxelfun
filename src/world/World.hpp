#pragma once

#include "../Input.hpp"

//#include "../camera/PerspectiveCamera.hpp"
#include "ChunkManager.h"
#include "../renderers/ChunkRenderer.h"
#include "../camera/Camera.hpp"

//#include <vector>
//#include <memory>

#include "../pch/pch_std.h"

class World
{
public:
    void init();
    void update(const float& timestep);
    //void render(const PerspectiveCamera& camera);
    void render(const Camera& camera);
   
    void destroy();

private:
    unsigned int m_chunk_size;

    ChunkManager m_chunk_manager;
    ChunkRenderer m_chunk_renderer;
 
};