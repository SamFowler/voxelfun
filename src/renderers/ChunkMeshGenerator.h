#pragma once

#include <vector>
#include <array>

#include "../world/Chunk.h"
#include "Renderables.h"
#include "ChunkMesh.hpp"
#include <GL/glew.h>




namespace ChunkMeshGenerator
{

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

    struct ChunkMeshFace
    {
        ChunkMeshFace() : colour(0), run_length(0), run_width(0), origin_i(0), origin_j(0) {};
        ChunkMeshFace(const ColourID& colour_id, const unsigned& length, const unsigned& width, const unsigned& i, const unsigned j) 
        : colour(colour_id), run_length(length), run_width(width), origin_i(i), origin_j(j) {};

        ColourID colour;
        unsigned run_length = 0;
        unsigned run_width = 0;

        unsigned origin_i = 0;
        unsigned origin_j = 0;
    };

    struct GreedyProcessState
    {
        GreedyProcessState(unsigned& direction_, const Chunk& chunk_, const unsigned& chunk_size_, const bool plusState)
        : direction(direction_), chunk_size(chunk_size_), chunk(chunk_) 
        {

            if (direction == 0) 
            {
                if (plusState) {
                    face = ChunkMeshGenerator::Y_PLUS_FACE;
                    normal_index = ChunkMeshGenerator::Y_PLUS_NORMAL_INDEX;
                } else {
                    face = ChunkMeshGenerator::Y_MINUS_FACE;
                    normal_index = ChunkMeshGenerator::Y_MINUS_NORMAL_INDEX; 
                }
            }
            else if (direction == 1)
            {
                if (plusState) {
                    face = ChunkMeshGenerator::X_PLUS_FACE;
                    normal_index = ChunkMeshGenerator::X_PLUS_NORMAL_INDEX;
                } else {
                    face = ChunkMeshGenerator::X_MINUS_FACE;
                    normal_index = ChunkMeshGenerator::X_MINUS_NORMAL_INDEX; 
                }
            }
            else if (direction == 2)
            {
                if (plusState) {
                    face = ChunkMeshGenerator::Z_PLUS_FACE;
                    normal_index = ChunkMeshGenerator::Z_PLUS_NORMAL_INDEX;
                } else {
                    face = Z_MINUS_FACE;
                    normal_index = Z_MINUS_NORMAL_INDEX; 
                }
            }

        };
        //GreedyProcessState(unsigned& normal_index_, unsigned& direction_, const Chunk& chunk_, const unsigned& chunk_size_, std::array<GLuint, 12> mesh_face)
        //: normal_index(normal_index_), direction(direction_), chunk_size(chunk_size_), chunk(chunk_), face(mesh_face) {};

        unsigned direction = 0;
        const unsigned chunk_size = 0;
        const Chunk& chunk;
        unsigned normal_index = 0;
        std::array<GLuint, 12> face;

        unsigned run_length = 0;

        ColourID current_colour = 0;
        ColourID previous_colour = 0;
        ChunkMeshFace previous_rectangle = {0,0,0,0,0};

    };

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

    void meshRectangle(ChunkMesh& mesh, const ChunkMeshFace& rectangle, const Chunk& chunk, const unsigned& direction, const unsigned& layer, const std::array<GLuint, 12>& face, unsigned& element_count);
    //const Voxel& getChunkVoxel(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& direction, const Chunk& chunk);
    ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& chunk_size, const unsigned& direction, const Chunk& chunk);
    ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Chunk& chunk, const unsigned& chunk_size, const unsigned& direction);

    bool isFaceVisible(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Chunk& chunk);
    unsigned getLocalIndex(const unsigned& i, const unsigned& j, const unsigned& chunk_size);
    void makeChunkMesh_Greedy (const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh);

    void makeChunkMesh_Optimal(const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh);

    void addFace(ChunkMesh& mesh, const Voxel& voxel, const VoxelInChunkPos& voxel_pos, const Colour& voxel_colour,
                    int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index);

//private:
    //unsigned int m_chunk_size;
    //unsigned int m_chunk_size_sq;
    //unsigned int m_chunk_volume;


};