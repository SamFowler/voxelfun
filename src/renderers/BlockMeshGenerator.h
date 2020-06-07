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

    struct GreedyProcessState
    {
        GreedyProcessState(unsigned& direction_, const Block& block_, const unsigned& block_size_, const bool plusState)
        : direction(direction_), block_size(block_size_), block(block_) 
        {

            if (direction == 0) 
            {
                if (plusState) {
                    face = BlockMeshGenerator::Y_PLUS_FACE;
                    normal_index = BlockMeshGenerator::Y_PLUS_NORMAL_INDEX;
                } else {
                    face = BlockMeshGenerator::Y_MINUS_FACE;
                    normal_index = BlockMeshGenerator::Y_MINUS_NORMAL_INDEX; 
                }
            }
            else if (direction == 1)
            {
                if (plusState) {
                    face = BlockMeshGenerator::X_PLUS_FACE;
                    normal_index = BlockMeshGenerator::X_PLUS_NORMAL_INDEX;
                } else {
                    face = BlockMeshGenerator::X_MINUS_FACE;
                    normal_index = BlockMeshGenerator::X_MINUS_NORMAL_INDEX; 
                }
            }
            else if (direction == 2)
            {
                if (plusState) {
                    face = BlockMeshGenerator::Z_PLUS_FACE;
                    normal_index = BlockMeshGenerator::Z_PLUS_NORMAL_INDEX;
                } else {
                    face = Z_MINUS_FACE;
                    normal_index = Z_MINUS_NORMAL_INDEX; 
                }
            }

        };
        //GreedyProcessState(unsigned& normal_index_, unsigned& direction_, const Block& block_, const unsigned& block_size_, std::array<GLuint, 12> mesh_face)
        //: normal_index(normal_index_), direction(direction_), block_size(block_size_), block(block_), face(mesh_face) {};

        unsigned direction = 0;
        const unsigned block_size = 0;
        const Block& block;
        unsigned normal_index = 0;
        std::array<GLuint, 12> face;

        unsigned run_length = 0;

        ColourID current_colour = 0;
        ColourID previous_colour = 0;
        BlockMeshFace previous_rectangle = {0,0,0,0,0};

    };

    /*
public:
    BlockMeshGenerator() 
        : m_block_size    (16), 
          m_block_size_sq (m_block_size*m_block_size),
          m_block_volume  (m_block_size*m_block_size*m_block_size)
        {};
    BlockMeshGenerator(const unsigned int& block_size) 
        : m_block_size    (block_size), 
          m_block_size_sq (block_size*block_size),
          m_block_volume  (block_size*block_size*block_size)
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