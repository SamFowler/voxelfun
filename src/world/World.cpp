#include "World.hpp"


void World::init()
{

    m_chunk_size = 8;

    m_chunk_manager = ChunkManager(m_chunk_size);
    m_chunk_manager.init();

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if((rand() % 2) == 0)
                m_chunk_manager.addChunk({i,-1,j}, ChunkMakeType::DIRT_CHUNK);
            else
                m_chunk_manager.addChunk({i,-1,j}, ChunkMakeType::GRASS_CHUNK);

        }   
    }
    //m_chunk_manager.addChunk({0,0,0}, ChunkMakeType::DIRT_CHUNK);
    //m_chunk_manager.addChunk({0,0,1}, ChunkMakeType::DIRT_CHUNK);
    //m_chunk_manager.addChunk({0,1,0}, ChunkMakeType::GRASS_CHUNK);
    //m_chunk_manager.addChunk({0,1,0}, ChunkMakeType::EMPTY_CHUNK);


        
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