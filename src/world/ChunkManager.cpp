#include "ChunkManager.h"

#include <iostream> //TODO: replace with log

bool ChunkManager::init() 
{
    /*
    //addChunk( {} )
    //Chunk (ChunkPos position, std::vector<Voxel> voxels, std::vector<Colour> colours, ChunkManager& manager_ptr);
    std::cout << "chunk manager init" << std::endl;
    ChunkPos pos = {0,0,0};
    Voxel voxel = {1, VoxelType::Grass};
    std::vector<Voxel> voxels(m_chunk_volume, voxel);
    std::vector<Colour> colours = { {0,0,0,0}, {255, 0, 255, 255} };

    addChunk(
        pos, voxels, colours
    );*/

    return true;
}

void ChunkManager::update(const Input& input) 
{

}

void ChunkManager::destroy()
{

}

void ChunkManager::addChunk(const ChunkPos& position, const ChunkMakeType& type)
{
    std::vector<Voxel> voxels;
    voxels.reserve(sizeof(Voxel)*m_chunk_volume);
    std::vector<Colour> colours;

    DefaultChunkMaker::makeChunk(type, voxels, colours, m_chunk_size);

    addChunk(position, voxels, colours);
}
void ChunkManager::addChunk(const ChunkPos& position, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours)
{
    
    auto it = m_chunks.find(position);
    if ( it == m_chunks.cend() )
    {
        
        std::cout << "Adding: " << std::endl;
        auto& chunk = m_chunks.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(position),
            std::forward_as_tuple(position, voxels, colours, *this)
        ).first->second;
        chunk.updateAllNeighbours();
        chunk.printChunk();
        std::cout << "chunk added" << std::endl;
        addChunkToUpdateList(position);
    }
}

void ChunkManager::replaceChunk(const Chunk& chunk)
{
    m_chunks.emplace( 
        std::piecewise_construct,
        std::forward_as_tuple(chunk.getPosition()),
        std::forward_as_tuple(chunk)
        );
}

void ChunkManager::addChunkToUpdateList(const ChunkPos& chunk_pos)
{
    std::cout << "adding chunk to update list" << std::endl;
    for (auto it : m_updated_chunk_list)
    {
        if (it->getPosition() == chunk_pos)
        { // chunk_pos is already in list of chunks to update, don't add to list
            return;
        }
    }
    std::cout << "chunk added to update list" << std::endl;
    m_updated_chunk_list.push_back(getChunkPtr(chunk_pos));
    std::cout << "chunk added to update list" << std::endl;

}

void ChunkManager::clearUpdatedChunkList()
{
    m_updated_chunk_list.clear();
}

std::vector<const Chunk*> ChunkManager::getUpdatedChunkList() const
{
    return m_updated_chunk_list;
}

const Chunk* ChunkManager::getChunkPtr(const ChunkPos& chunk_pos) const
{
    auto it = m_chunks.find(chunk_pos);
    if (it != m_chunks.cend())
    {
        return &(it->second);
    }
    else
    {
        std::cout << "Could not find chunk: pos{" << chunk_pos.pos.x << "," << chunk_pos.pos.y << "," << chunk_pos.pos.z << "}" << std::endl;
    }
    
    return nullptr;
}
