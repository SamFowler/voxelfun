#include "World.h"


void World::init()
{

    m_block_renderer.init();

    for (int z = 0; z < 4; z++)
    {
        for (int x = 0; x < 4; x++)
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
    
    m_sector_manager.draw({0});
}


void World::destroy()
{
    m_block_renderer.destroy();    
}