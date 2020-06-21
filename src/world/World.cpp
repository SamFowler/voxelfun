#include "World.h"

#include "../renderers/Frustum.h"

void World::init()
{

    m_block_renderer.init();

    for (int z = 0; z < 8; z++)
    {
        for (int x = 0; x < 8; x++)
        {
            m_sector_manager.generateWorld({0,0,0}, {x,0,z});
        }
    }

    // m_selected_region = SelectedRegion({0,0,0}, {0,0,1}, {0,0,1});
    // m_block_renderer.addSelectorVAO(m_selected_region.getWorldPos());

}
 
void World::update(Input& input, const float& timestep)
{
    m_sector_manager.update();

    // handle the voxel selector
    m_selected_region.moveRegion(input);

    if (input.wasKeyPressed(SDLK_RETURN))
    {
        //TODO create some form of WorldEditor class to handle input for map editing
        // m_sector_manager.getSector(m_selected_region.getSectorPos()).editBlock(m_selected_region.getBlockPos());
        // m_sector_manager.getSector(m_selected_region.getSectorPos()).updateBlocks(m_block_renderer.getRefToRemeshList());
    }

    m_block_renderer.updateSettings(input);
}


void World::render(const Camera& camera)
{
    m_block_renderer.draw(camera);
    
    Frustum frustum;
    frustum.getPlanes(camera.getProjectionViewMatrix());

    uint32_t num_draws = 0;
    m_sector_manager.draw(frustum, {0}, num_draws);
    std::cout << "num_draws: " << num_draws << std::endl;
}


void World::destroy()
{
    m_block_renderer.destroy();    
}