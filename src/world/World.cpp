#include "World.hpp"

void World::init()
{

    m_chunk_manager = ChunkManager(2);
    m_chunk_manager.init();
        
    m_chunk_renderer.init();

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