#pragma once

#include "../pch/pch_std.h"

#include "../Input.h"
#include "BlockManager.h"
#include "../renderers/BlockRenderer.h"
#include "../camera/Camera.h"

#include "SectorManager.h"
#include "SelectedRegion.h"
#include "TerrainGenerator.h"

class World
{
public:
    World(unsigned int block_size) : m_block_size(block_size), m_terrain_generator(1), m_sector_manager(block_size) {};
    void init();
    
    void update(Input& input, const float& timestep);
    void render(const Camera& camera);
   
    void destroy();

private:
    unsigned int m_block_size;

    TerrainGenerator m_terrain_generator;

    BlockRenderer m_block_renderer;

    SectorManager m_sector_manager;

    SelectedRegion m_selected_region;

};