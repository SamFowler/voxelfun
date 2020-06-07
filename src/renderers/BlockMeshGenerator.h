#pragma once

#include "../pch/pch_std.h"

#include "../world/Block.h"
#include "BlockMesh.h"

namespace BlockMeshGenerator
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

    struct BlockMeshFace
    {
        BlockMeshFace() : colour(0), run_length(0), run_width(0), origin_i(0), origin_j(0) {};
        BlockMeshFace(const ColourID& colour_id, const unsigned& length, const unsigned& width, const unsigned& i, const unsigned j) 
        : colour(colour_id), run_length(length), run_width(width), origin_i(i), origin_j(j) {};

        ColourID colour;
        unsigned run_length = 0;
        unsigned run_width = 0;

        unsigned origin_i = 0;
        unsigned origin_j = 0;
    };

    enum MeshMethod {
        NAIVE_MESH = 0,
        CULL_MESH_FAST,
        CULL_MESH_OPTIMAL,
        GREEDY_MESH,
        OPTIMAL_MESH,
        COUNT
    };

    VertexArrayObject makeBlockVAO(const Block& block, const unsigned int& block_size, const MeshMethod& mesh_method = CULL_MESH_FAST);
    void makeBlockMesh_Naive  (const Block& block, const unsigned int& block_size, BlockMesh& block_mesh);
    void makeBlockMesh_Culling(const Block& block, const unsigned int& block_size, BlockMesh& block_mesh);

    void meshRectangle(BlockMesh& mesh, const BlockMeshFace& rectangle, const Block& block, const unsigned& direction, const unsigned& layer, const std::array<GLuint, 12>& face, unsigned& element_count);
    //const Voxel& getBlockVoxel(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& direction, const Block& block);
    ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& block_size, const unsigned& direction, const Block& block);
    ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Block& block, const unsigned& block_size, const unsigned& direction);

    bool isFaceVisible(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Block& block);
    unsigned getLocalIndex(const unsigned& i, const unsigned& j, const unsigned& block_size);
    void makeBlockMesh_Greedy (const Block& block, const unsigned int& block_size, BlockMesh& block_mesh);

    void makeBlockMesh_Optimal(const Block& block, const unsigned int& block_size, BlockMesh& block_mesh);

    void addFace(BlockMesh& mesh, const Voxel& voxel, const VoxelPos& voxel_pos, const Colour& voxel_colour,
                    int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index);

//private:
    //unsigned int m_block_size;
    //unsigned int m_block_size_sq;
    //unsigned int m_block_volume;


};