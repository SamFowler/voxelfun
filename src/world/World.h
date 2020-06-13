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
    World() : m_terrain_generator(1){};
    void init();
    
    void update(Input& input, const float& timestep);
    void render(const Camera& camera);
   
    void destroy();

private:

    TerrainGenerator m_terrain_generator;

    BlockRenderer m_block_renderer;

    SectorManager m_sector_manager;

    SelectedRegion m_selected_region;

};