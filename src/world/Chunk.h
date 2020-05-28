#pragma once

#include <vector>
#include <queue>
#include <glm/vec3.hpp>

#include "Voxel.h"
#include "Coordinates.h"
#include "Colour.h"


class ChunkManager;

class Chunk
{
public:
    //Constructors
    Chunk (Chunk chunk, ChunkManager& manager_ptr);
    Chunk (const ChunkPos& position, ChunkManager& manager);
    Chunk (ChunkPos position, std::vector<Voxel> voxels, std::vector<Colour> colours, ChunkManager& manager);

    // Helpers
    unsigned int    indexFromInChunkPos   (const VoxelInChunkPos& voxel_coord) const;
    VoxelInChunkPos inChunkPosFromIndex   (const unsigned int&    index      ) const;

    bool isChunkEdge  (const VoxelInChunkPos& voxel_coord) const;
    bool isChunkEdge  (const int&             voxel_index) const;

    ColourID addColour(const Colour& colour);
    void removeColour (const Colour& colour);
    void removeColour (const ColourID& colour_id);
    void removeAllColours();
    ColourID findColour (const Colour& colour) const;

    // Getters
    ChunkPos    getPosition   () const  { return m_position;   }

    Colour     getColour       (const ColourID&        colour_id  ) const;
    Colour     getVoxelColour  (const VoxelInChunkPos& voxel_coord) const;
    VoxelType  getVoxelType    (const VoxelInChunkPos& voxel_coord) const;
    const Voxel&    getVoxel        (const VoxelInChunkPos& voxel_coord) const;
    VoxelInChunkPos getTopVoxelPos (const VoxelInChunkPos& voxel_coord)  const;

    const std::vector<Voxel>& getVoxelDataRef() const;
    const std::vector<Colour>& getColoursRef() const;

    // Setters
    void setPosition(const ChunkPos& position) { m_position = position; }
    
    void setVoxels(const std::vector<VoxelInChunkPos>& voxel_coords, const Colour&    colour);
    void setVoxels(const std::vector<VoxelInChunkPos>& voxel_coords, const VoxelType& type  );
    void setVoxels(const std::vector<VoxelInChunkPos>& voxel_coords, const Voxel&     voxel );

    void updateNeighbours(const VoxelInChunkPos& voxel_coord);
    void updateAllNeighbours();

    void changeAllVoxels(const Colour&    colour);
    void changeAllVoxels(const VoxelType& type);
    void changeAllVoxels(const Voxel&     voxel);

    void changeVoxelsFromTo(const Colour&    from_colour, const Colour&    to_colour);
    void changeVoxelsFromTo(const VoxelType& from_type,   const VoxelType& to_type  );
    void changeVoxelsFromTo(const Voxel&     from_voxel,  const Voxel&     to_voxel );

    //Debug
    void printChunk(const bool printVoxels = false) const;


private:

    // Data
    std::vector<Voxel>  m_voxel_data;

    std::vector<Colour> m_chunk_colours;
    std::queue<ColourID> m_free_colour_ids;

    ChunkManager& mp_manager;

    ChunkPos   m_position;
    //glm::ivec3 m_dimensions;
    //size_t     m_volume;

    bool m_remesh;
    //bool m_is_empty;

};