#pragma once

//#include <unordered_map>
//#include <queue>
//#include <vector>
//#include <utility>

#include "../pch/pch_std.h"

#include "Chunk.h"

#include "../Input.hpp" // TODO: unsure if this should go here or not

#include "DefaultChunkMaker.h"

class ChunkManager
{
public:
    friend class Chunk;
    //friend class ChunkMeshGenerator;

    // Constructors
    ChunkManager(const size_t& chunk_size = 2) : m_chunk_size(chunk_size), 
                                             m_chunk_size_sq(chunk_size*chunk_size),
                                             m_chunk_volume(chunk_size*chunk_size*chunk_size)
                                             {};
    //ChunkManager(const Chunk& chunk);
    //ChunkManager(const std::vector<Chunk>& chunks);

    // Processors
    bool init();
    void update(const Input& input);
    void destroy();

    // Getters
    int getNumChunks() const;
    
    void addChunk(const ChunkPos& position, const ChunkMakeType&);
    void addChunk(const ChunkPos& position, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours);
    //void addChunk    (const Chunk&              chunk          );
    //void addChunks   (const std::vector<Chunk>& chunks         );
    void replaceChunk(const Chunk&              chunk          );
    void addChunkToUpdateList(const ChunkPos& chunk_pos);

    void clearUpdatedChunkList();
    std::vector<const Chunk*> getUpdatedChunkList() const;
    
    const Chunk* getChunkPtr(const ChunkPos& chunk_pos) const; 

    Voxel              getVoxel (const VoxelWorldPos&              voxel_world_pos       ) const;
    std::vector<Voxel> getVoxels(const std::vector<VoxelWorldPos>& voxel_world_positions ) const;

    // Public setters (take in voxel world coordinates and call private functions with chunk/voxel positions)
    void setVoxels      (const std::vector<VoxelWorldPos>& voxel_world_positions, const Voxel& new_voxel);
    void setVoxelsColour(const std::vector<VoxelWorldPos>& voxel_world_positions, const Colour& new_colour);
    void setVoxelsType  (const std::vector<VoxelWorldPos>& voxel_world_positions, const VoxelType& new_type);

private:
    // Helpers
    bool chunkExists (const ChunkPos&           chunk_position ) const;
    bool removeChunk (const ChunkPos&           chunk_position );

    ChunkAndVoxelPos getChunkVoxelPosFromVoxelWorldPos(const VoxelWorldPos& voxel_world_pos) const;

    //void addColourToChunk (...) //TODO: unsure about this being here at the moment
    //removeColourFromChukn (...) //TODO: unsure about this being here at the moment

    // Private getters
    //const Chunk&              getChunk  (const ChunkPos&                chunk_position  ) const;
    //const std::vector<Chunk>& getChunks (const std::vector<ChunkPos>&   chunk_positions ) const;

    Voxel              getVoxel  (const ChunkAndVoxelPos&     chunk_voxel_pos      ) const;
    std::vector<Voxel> getVoxels (const ChunkAndManyVoxelPos& chunk_voxel_positions) const;

private:

    // Private setters
    void setVoxelsInChunk      (const ChunkPos& chunk_position, const std::vector<glm::ivec3>& chunk_voxel_positions, const Voxel& new_voxel);
    void setVoxelColoursInChunk(const ChunkPos& chunk_position, const std::vector<glm::ivec3>& chunk_voxel_positions, const Colour& new_colour);
    void setVoxelTypesInChunk  (const ChunkPos& chunk_position, const std::vector<glm::ivec3>& chunk_voxel_positions, const VoxelType& new_type);

    // Data
    std::unordered_map<ChunkPos, Chunk, ChunkPositionHash> m_chunks;
    int m_num_chunks;

    //std::queue<> m_updated_chunk_list;
    std::vector<const Chunk*> m_updated_chunk_list;

    unsigned int m_chunk_size;
    unsigned int m_chunk_size_sq;
    unsigned int m_chunk_volume;

};