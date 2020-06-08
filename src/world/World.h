#pragma once

#include "../pch/pch_std.h"

#include "../Input.h"
#include "BlockManager.h"
#include "../renderers/BlockRenderer.h"
#include "../camera/Camera.h"

#include "Sector.h"
#include "SectorManager.h"

class World
{
public:
    World(unsigned int block_size) : m_block_size(block_size), m_sector(block_size), m_sector_manager(block_size) {};
    void init();
    void update(const float& timestep);
    void render(const Camera& camera);
   
    void destroy();

private:
    unsigned int m_block_size;

     Sector m_sector;

    //BlockManager m_block_manager;
    BlockRenderer m_block_renderer;

    SectorManager m_sector_manager;

};