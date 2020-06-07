#include "World.hpp"


void World::init()
{

    m_block_size = 8;

    m_block_manager = BlockManager(m_block_size);
    m_block_manager.init();
    
    for (int i = 0; i < 45; i++)
    {
        for (int j = 0; j < 45; j++)
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
                m_block_manager.addBlock({i,3,j}, BlockMakeType::TREE_CHUNK);
                m_block_manager.addBlock({i,4,j}, BlockMakeType::TREE_CHUNK);
                m_block_manager.addBlock({i,5,j}, BlockMakeType::TREE_CHUNK);
            }
        }   
    }
    

    //m_block_manager.addBlock({1,2,1}, BlockMakeType::GRASS_CHUNK);
    //m_block_manager.addBlock({0,0,1}, BlockMakeType::GRASS_CHUNK);

    //m_block_manager.addBlock({1,0,0}, BlockMakeType::GRASS_CHUNK);
    //m_block_manager.addBlock({0,0,0}, BlockMakeType::RANDOM_CHUNK);
   
    m_block_manager.addBlock({10, 15, 10}, BlockMakeType::LIGHT_CHUNK);
  
    //m_block_manager.addBlock({-2, -1, -2}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-2, -1, -3}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-3, -1, -2}, BlockMakeType::RANDOM_CHUNK);
    //m_block_manager.addBlock({-3, -1, -3}, BlockMakeType::RANDOM_CHUNK);
//
    //m_block_manager.addBlock({-1, -1, -5}, BlockMakeType::DEBUG_CHUNK);

    //m_block_manager.addBlock({-3, -1, -3}, BlockMakeType::REVEAL_DIRT_CHUNK);
        
    m_block_renderer.init(m_block_size);

}

void World::update(const float& timestep)
{
    //m_block_manager.updateBlocks();
    //m_block_manager.updateVoxelNeighbours();

    m_block_renderer.getNewBlockUpdates(
        m_block_manager.getUpdatedBlockList()
    );
    m_block_manager.clearUpdatedBlockList();
    m_block_renderer.updateVAOs();
}


//void World::render(const PerspectiveCamera& camera)
void World::render(const Camera& camera)
{
    m_block_renderer.draw(camera);

}


void World::destroy()
{
    m_block_renderer.destroy();    
    m_block_manager.destroy();
}