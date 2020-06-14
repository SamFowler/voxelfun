#pragma once

#include "../pch/pch_std.h"

#include "../world/Block.h"
#include "BlockMesh.h"

class SectorColours;

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
        BlockMeshFace() : run_length(0), run_width(0), origin_i(0), origin_j(0) {};
        BlockMeshFace(const Voxel& voxel_, const unsigned& length, const unsigned& width, const unsigned& i, const unsigned j) 
        : voxel(voxel_), run_length(length), run_width(width), origin_i(i), origin_j(j) {};

        Voxel voxel;
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

    VertexArrayObject makeBlockVAO(const Block& block, const SectorColours& sector_colours, const MeshMethod& mesh_method = CULL_MESH_FAST);
    void makeBlockMesh_Naive  (const Block& block, BlockMesh& block_mesh);
    void makeBlockMesh_Culling(const Block& block, BlockMesh& block_mesh, const SectorColours& sector_colours);

    void meshRectangle(BlockMesh& mesh, const BlockMeshFace& rectangle, const Block& block, const unsigned& direction, 
                const unsigned& layer, const std::array<GLuint, 12>& face, unsigned& element_count, const SectorColours& sector_colours);
    //const Voxel& getBlockVoxel(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& direction, const Block& block);
    Voxel getVoxel(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& direction, const Block& block);
    Voxel getVoxel(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Block& block, const unsigned& direction);

    bool isFaceVisible(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Block& block);
    unsigned getLocalIndex(const unsigned& i, const unsigned& j);
    void makeBlockMesh_Greedy (const Block& block, BlockMesh& block_mesh, const SectorColours& sector_colours);

    void makeBlockMesh_Optimal(const Block& block, BlockMesh& block_mesh);

    void addFace(BlockMesh& mesh, const Voxel& voxel, const VoxelPos& voxel_pos, const Colour& voxel_colour,
                    int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index);

};