#include "ChunkManager.h"

#include <iostream> //TODO: replace with log

#include "../rendering/ChunkMeshGenerator.h"

bool ChunkManager::init() 
{
    //addChunk( {} )
    //Chunk (ChunkPos position, std::vector<Voxel> voxels, std::vector<Colour> colours, ChunkManager& manager_ptr);
    std::cout << "chunk manager init" << std::endl;
    ChunkPos pos = {0,0,0};
    Voxel voxel = {1, VoxelType::Grass};
    std::vector<Voxel> voxels(m_chunk_volume, voxel);
    std::vector<NColour> colours = { {0,0,0,0}, {255, 0, 255, 255} };

    addChunk(
        pos, voxels, colours
    );

    return true;
}

std::vector<ChunkPos> ChunkManager::update(const Input& input) 
{
    //std::cout << "manager update" << std::endl;
    /*
    std::pair<bool, const Chunk&> got_chunk = getChunk({0,0,0});
    if (got_chunk.first)
    {
        got_chunk.second.printChunk(true);
    }*/
     //getChunkPtr({0,0,0})->printChunk(true);;

    return std::vector<ChunkPos>(3);
}

void ChunkManager::addChunk(const ChunkPos& position, const std::vector<Voxel>& voxels, const std::vector<NColour>& colours)
{
    
    auto it = m_chunks.find(position);
    if ( it == m_chunks.cend() )
    {
        
        std::cout << "Adding: " << std::endl;
        auto chunk = m_chunks.emplace(
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
/*
void ChunkManager::addChunk(const Chunk& chunk)
{
    auto it = m_chunks.find(chunk.getPosition());
    if(it == m_chunks.end())
    {
        m_chunks.emplace( 
            std::piecewise_construct,
            std::forward_as_tuple(chunk.getPosition()),
            std::forward_as_tuple(chunk, *this)
            );
    }
}
void ChunkManager::addChunks(const std::vector<Chunk>& chunks)
{
    for (auto chunk : chunks)
    {
        addChunk(chunk);
    }
}
*/
void ChunkManager::replaceChunk(const NChunk& chunk)
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


    m_chunk_update_list.push_back(chunk_pos);

}

void ChunkManager::clearUpdatedChunkList()
{
    m_updated_chunk_list.clear();
}

std::vector<const NChunk*> ChunkManager::getUpdatedChunkList() const
{
    return m_updated_chunk_list;

}

//void ChunkManager::updateUpdatedChunkList(const std::vector<const Chunk*>& chunks_still_to_update)
//{
//    m_updated_chunk_list = chunks_still_to_update;
//}


//const Chunk& ChunkManager::getChunk(const VoxelWorldPos& voxel_world_pos) const
//{
    //return m_chunk[]
//}

//std::pair<bool, const Chunk&> ChunkManager::getChunk(const ChunkPos& chunk_pos) const;
/*
std::pair<bool, const Chunk&> ChunkManager::getChunk(const ChunkPos& chunk_pos) const
{
    auto it = m_chunks.find(chunk_pos);
    if (it != m_chunks.end())
    {
        return std::make_pair(true, it->second);
    }
    return std::make_pair(false, it->second);
    //return m_chunks[chunk_pos]
}
*/



const NChunk* ChunkManager::getChunkPtr(const ChunkPos& chunk_pos) const
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

void ChunkManager::updateVAOs(std::vector<VertexArrayObject>& chunk_vaos)
{
    for (auto chunk_pos : m_chunk_update_list)
    {
        //NChunk& chu = m_chunks.find(chunk_pos)->second;
        //chu->second
        //NChunk chunk = m_chunks[chunk_pos];
        //VertexArrayObject vao = ChunkMeshGenerator::makeChunkVAO(m_chunks[chunk_pos], m_chunk_size));
        chunk_vaos.push_back(ChunkMeshGenerator::makeChunkVAO(m_chunks.find(chunk_pos)->second, m_chunk_size));

    }
}