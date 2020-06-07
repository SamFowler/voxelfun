#pragma once

#include "../pch/pch_std.h"

#include "../Input.h"
#include "BlockManager.h"
#include "../renderers/BlockRenderer.h"
#include "../camera/Camera.h"


class World
{
public:
    void init();
    void update(const float& timestep);
    void render(const Camera& camera);
   
    void destroy();

private:
    unsigned int m_block_size;

    BlockManager m_block_manager;
    BlockRenderer m_block_renderer;
 
};