#pragma once


#include <array>
#include <vector>

#include "Block.hpp" 
#include "Mesh.hpp"

enum MeshMethod {
    NAIVE_MESH = 0,
    CULL_MESH_FAST,
    CULL_MESH_OPTIMAL,
    GREEDY_MESH,
    OPTIMAL_MESH,
    COUNT
};

//using Colour = glm::vec4;
//using VoxelID = unsigned int;
//TODO: can i do:
//using Colour; // or class Colour?
//using VoxelID;?

namespace BlockMeshGenerator
{
    bool isBlockEdge(const glm::ivec3& position, const int& size);
    int getVoxelIndex(const glm::ivec3& voxel_position, const int& size);
    std::array<bool, 6> getNeighbours(const glm::ivec3& vox_pos, const Block& block);
    std::array<bool, 6> getNeighbours_safe(const glm::ivec3& vox_pos, const Block& block);

    bool doesNeighbourExist(const glm::ivec3& neighbour_position, const Block& block);
    bool doesNeighbourExist_safe(const glm::ivec3& neighbour_position, const Block& block);
    void addFace(Mesh& mesh, const std::vector<GLuint>& face_verts, const glm::ivec3& voxel_pos, int& element_count, const Colour& colour, const glm::vec3& normal);


    char getNeighboursByte_safe(const glm::ivec3& vox_pos, const Block& block);
    char getNeighboursByte(const glm::ivec3& vox_pos, const Block& block);
    std::vector<char> getAllNeighbours(const Block& block);


    VertexArrayObject makeBlockVAO(const Block& block, const MeshMethod& mesh_method = CULL_MESH_FAST);
    Mesh makeBlockMesh_Naive(const Block& block);
    Mesh makeBlockMesh_Culling(const Block& block);
    Mesh makeBlockMesh_Greedy(const Block& block);
    Mesh makeBlockMesh_Optimal(const Block& block);
}