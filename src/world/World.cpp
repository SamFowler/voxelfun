#include "World.hpp"


void World::init()
{

    m_chunk_size = 32;

    m_chunk_manager = ChunkManager(m_chunk_size);
    m_chunk_manager.init();


    m_chunk_manager.addChunk({0,0,0}, ChunkMakeType::DIRT_CHUNK);
    m_chunk_manager.addChunk({0,0,1}, ChunkMakeType::DIRT_CHUNK);
    m_chunk_manager.addChunk({0,1,0}, ChunkMakeType::GRASS_CHUNK);
    m_chunk_manager.addChunk({0,1,0}, ChunkMakeType::EMPTY_CHUNK);


        
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
    m_chunk_renderer.updateVAOs(m_chunk_size);
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