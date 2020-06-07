#pragma once

#include "../Input.hpp"

//#include "../camera/PerspectiveCamera.hpp"
#include "BlockManager.h"
#include "../renderers/BlockRenderer.h"
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
    unsigned int m_block_size;

    BlockManager m_block_manager;
    BlockRenderer m_block_renderer;
 
};