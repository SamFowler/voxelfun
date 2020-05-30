#include "World.hpp"


void World::init()
{

    m_chunk_size = 8;

    m_chunk_manager = ChunkManager(m_chunk_size);
    m_chunk_manager.init();
    
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            if((rand() % 6) == 0)
                m_chunk_manager.addChunk({i,-1,j}, ChunkMakeType::DIRT_CHUNK);
            else
                m_chunk_manager.addChunk({i,-1,j}, ChunkMakeType::GRASS_CHUNK);


            if((rand() % 40) == 0)
            {
                m_chunk_manager.addChunk({i,0,j}, ChunkMakeType::TREE_CHUNK);
                m_chunk_manager.addChunk({i,1,j}, ChunkMakeType::TREE_CHUNK);
                m_chunk_manager.addChunk({i,2,j}, ChunkMakeType::TREE_CHUNK);
            }
        }   
    }
    

    //m_chunk_manager.addChunk({1,2,1}, ChunkMakeType::GRASS_CHUNK);
    //m_chunk_manager.addChunk({0,0,1}, ChunkMakeType::GRASS_CHUNK);

   //m_chunk_manager.addChunk({1,0,0}, ChunkMakeType::GRASS_CHUNK);
   //m_chunk_manager.addChunk({0,0,0}, ChunkMakeType::RANDOM_CHUNK);
   
    m_chunk_manager.addChunk({10, 15, 10}, ChunkMakeType::LIGHT_CHUNK);

    m_chunk_manager.addChunk({-2, -1, -2}, ChunkMakeType::RANDOM_CHUNK);
    m_chunk_manager.addChunk({-2, -1, -3}, ChunkMakeType::RANDOM_CHUNK);
    m_chunk_manager.addChunk({-3, -1, -2}, ChunkMakeType::RANDOM_CHUNK);
    m_chunk_manager.addChunk({-3, -1, -3}, ChunkMakeType::RANDOM_CHUNK);

    m_chunk_manager.addChunk({-1, -1, -5}, ChunkMakeType::DEBUG_CHUNK);


        
    m_chunk_renderer.init(m_chunk_size);

}

void World::update(const float& timestep)
{
    //m_chunk_manager.updateChunks();
    //m_chunk_manager.updateVoxelNeighbours();

    m_chunk_renderer.getNewChunkUpdates(
        m_chunk_manager.getUpdatedChunkList()
    );
    m_chunk_manager.clearUpdatedChunkList();
    m_chunk_renderer.updateVAOs();
}


void World::render(const PerspectiveCamera& camera)
{
    m_chunk_renderer.draw(camera);

}


void World::destroy()
{
    m_chunk_renderer.destroy();    
    m_chunk_manager.destroy();
}