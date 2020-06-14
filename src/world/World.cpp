#include "World.h"


void World::init()
{


    /* 
    m_block_manager.init();
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if((rand() % 6) == 0)
                m_block_manager.addBlock({i,-1,j}, BlockMakeType::REVEAL_DIRT_CHUNK);
            else
                m_block_manager.addBlock({i,-1,j}, BlockMakeType::GRASS_CHUNK);


            if((rand() % 60) == 0)
            {
                m_block_manager.addBlock({i,0,j}, BlockMakeType::TREE_CHUNK);
                m_block_manager.addBlock({i,1,j}, BlockMakeType::TREE_CHUNK);
                m_block_manager.addBlock({i,2,j}, BlockMakeType::TREE_CHUNK);
                //m_block_manager.addBlock({i,3,j}, BlockMakeType::TREE_CHUNK);
                //m_block_manager.addBlock({i,4,j}, BlockMakeType::TREE_CHUNK);
                //m_block_manager.addBlock({i,5,j}, BlockMakeType::TREE_CHUNK);
            }
        }   
    } */
    

    //m_block_manager.addBlock({1,2,1}, BlockMakeType::GRASS_CHUNK);
    //m_block_manager.addBlock({0,0,1}, BlockMakeType::GRASS_CHUNK);
    //m_block_manager.addBlock({1,0,0}, BlockMakeType::GRASS_CHUNK);
    //m_block_manager.addBlock({0,0,0}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({10, 15, 10}, BlockMakeType::LIGHT_CHUNK);
    //m_block_manager.addBlock({-2, -1, -2}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-2, -1, -3}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-3, -1, -2}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-3, -1, -3}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-1, -1, -5}, BlockMakeType::DEBUG_CHUNK);
    //m_block_manager.addBlock({-3, -1, -3}, BlockMakeType::REVEAL_DIRT_CHUNK);
        
    

    m_block_renderer.init();

    std::vector<std::pair<const BlockPos, Block&>>& initial_mesh_list = m_block_renderer.getRefToRemeshList();

    SectorPos sector_pos = {0,0,0};
    Sector* p_sector = m_sector_manager.addSector(sector_pos);

    /* for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {    
            // if((rand() % 6) == 0)
            //     initial_mesh_list.push_back(p_sector->addBlock({i,0,j}, BlockMakeType::REVEAL_DIRT_CHUNK));
            // else
            //     initial_mesh_list.push_back(p_sector->addBlock({i,0,j}, BlockMakeType::GRASS_CHUNK));
            //initial_mesh_list.push_back(p_sector->addBlock({0,0,1}, BlockMakeType::REVEAL_DIRT_CHUNK));
            //initial_mesh_list.push_back(p_sector->addBlock({0,0,2}, BlockMakeType::REVEAL_DIRT_CHUNK));
            //initial_mesh_list.push_back(p_sector->addBlock({0,0,3}, BlockMakeType::REVEAL_DIRT_CHUNK));
            BlockPos block_pos = {i,0,j};
            std::pair<const BlockPos, Block &> block_pair = p_sector->addBlock(block_pos, BlockMakeType::EMPTY_CHUNK);
            m_terrain_generator.generateBlock(block_pair.second, CoordinateConversion::getWorldPos(sector_pos, block_pos, {0,0,0}));
            p_sector->updateBlockNeighbours(block_pos);
            initial_mesh_list.push_back(block_pair);
        }
    } */



    std::vector<std::pair<const BlockPos, Block &>> blocks_to_mesh = m_terrain_generator.generateSector(p_sector, sector_pos);
    for (auto it : blocks_to_mesh)
    {
        initial_mesh_list.push_back(it);
    }


    sector_pos = {1,0,0};
    p_sector = m_sector_manager.addSector(sector_pos);
    blocks_to_mesh = m_terrain_generator.generateSector(p_sector, sector_pos);
    for (auto it : blocks_to_mesh)
    {
        initial_mesh_list.push_back(it);
    }

    //std::pair<const BlockPos, Block &> block_pair = p_sector->addBlock({0,0,0}, BlockMakeType::EMPTY_CHUNK);
    //m_terrain_generator.generateBlock(block_pair.second, CoordinateConversion::getWorldPos({0,0,0}, {0,0,0}, {0,0,0}));
    //initial_mesh_list.push_back(block_pair);
   


    m_selected_region = SelectedRegion({0,0,0}, {0,0,1}, {0,0,1});
    
    m_block_renderer.addSelectorVAO(m_selected_region.getWorldPos());




    /* m_sector = Sector();

    m_block_renderer.getRefToRemeshList().push_back(m_sector.addBlock({1, 1, 1}, BlockMakeType::REVEAL_DIRT_CHUNK));
    m_block_renderer.getRefToRemeshList().push_back(m_sector.addBlock({1, 1, 4}, BlockMakeType::GRASS_CHUNK));
     for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            m_block_renderer.getRefToRemeshList().push_back(m_sector.addBlock({i, 0, j}, BlockMakeType::GRASS_CHUNK));
      
        }    
    }  */

    //m_block_manager.addBlock({i,-1,j}, BlockMakeType::REVEAL_DIRT_CHUNK);


}

void World::update(Input& input, const float& timestep)
{

    // handle the voxel selector
    m_selected_region.moveRegion(input);
    m_block_renderer.updateSelectorPosition(m_selected_region.getWorldPos());

    if (input.wasKeyPressed(SDLK_RETURN))
    {
        //TODO create some form of WorldEditor class to handle input for map editing
        //Voxel& voxel = m_sector_manager.getVoxel(m_selected_region.getSectorPos(), m_selected_region.getBlockPos(), m_selected_region.getVoxelPos());
        m_sector_manager.getSector(m_selected_region.getSectorPos()).editBlock(m_selected_region.getBlockPos());
        m_sector_manager.getSector(m_selected_region.getSectorPos()).updateBlocks(m_block_renderer.getRefToRemeshList());
        ///Block& block = m_sector_manager.getBlock(m_selected_region.getSectorPos(), m_selected_region.getBlockPos()).
    }

    
    m_block_renderer.updateSettings(input);
    m_block_renderer.updateVAOs(m_sector_manager.getSector({0,0,0}).colours /* this is temp here before renderer gets moved */);
}


void World::render(const Camera& camera)
{
    m_block_renderer.draw(camera);

}


void World::destroy()
{
    m_block_renderer.destroy();    
   // m_block_manager.destroy();
}