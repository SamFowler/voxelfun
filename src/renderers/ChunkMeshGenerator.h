#pragma once

#include <vector>
#include <array>

#include "../world/Chunk.h"
#include "Renderables.h"
#include "ChunkMesh.hpp"
#include <GL/glew.h>




namespace ChunkMeshGenerator
{
    /*
public:
    ChunkMeshGenerator() 
        : m_chunk_size    (16), 
          m_chunk_size_sq (m_chunk_size*m_chunk_size),
          m_chunk_volume  (m_chunk_size*m_chunk_size*m_chunk_size)
        {};
    ChunkMeshGenerator(const unsigned int& chunk_size) 
        : m_chunk_size    (chunk_size), 
          m_chunk_size_sq (chunk_size*chunk_size),
          m_chunk_volume  (chunk_size*chunk_size*chunk_size)
        {};
*/

    enum MeshMethod {
        NAIVE_MESH = 0,
        CULL_MESH_FAST,
        CULL_MESH_OPTIMAL,
        GREEDY_MESH,
        OPTIMAL_MESH,
        COUNT
    };

    VertexArrayObject makeChunkVAO(const Chunk& chunk, const unsigned int& chunk_size, const MeshMethod& mesh_method = CULL_MESH_FAST);
    void makeChunkMesh_Naive  (const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh);
    void makeChunkMesh_Culling(const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh);
    void makeChunkMesh_Greedy (const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh);
    void makeChunkMesh_Optimal(const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh);

    void addFace(ChunkMesh& mesh, const Voxel& voxel, const VoxelInChunkPos& voxel_pos, const Colour& voxel_colour,
                    int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index);

//private:
    //unsigned int m_chunk_size;
    //unsigned int m_chunk_size_sq;
    //unsigned int m_chunk_volume;

    const std::array<GLuint, 12> X_MINUS_FACE = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0};
    const std::array<GLuint, 12> Y_MINUS_FACE = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1};
    const std::array<GLuint, 12> Z_MINUS_FACE = {0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    const std::array<GLuint, 12> X_PLUS_FACE =  {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1};
    const std::array<GLuint, 12> Y_PLUS_FACE =  {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
    const std::array<GLuint, 12> Z_PLUS_FACE =  {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1};

    const GLuint X_MINUS_NORMAL_INDEX = 0;
    const GLuint X_PLUS_NORMAL_INDEX  = 1;
    const GLuint Y_MINUS_NORMAL_INDEX = 2;
    const GLuint Y_PLUS_NORMAL_INDEX  = 3;
    const GLuint Z_MINUS_NORMAL_INDEX = 4;
    const GLuint Z_PLUS_NORMAL_INDEX  = 5;
};