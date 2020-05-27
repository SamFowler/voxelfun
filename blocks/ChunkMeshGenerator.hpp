#pragma once

#include "Mesh.hpp"
//#include "Block.hpp"
#include "BChunk.hpp"
#include "BlockManager.hpp"

#include <unordered_map>



namespace ChunkMeshGenerator {

void addFace(Mesh& mesh, const std::vector<GLuint>& face_verts, const glm::ivec3& block_plus_voxel_pos, int& element_count, const Colour& colour, const glm::vec3& normal);    
void addBlockToMesh(const Block* block, Mesh& chunk_mesh, int& element_count, const glm::ivec3& block_pos);
Mesh makeChunkMesh_Culling(const std::vector<BlockID>& blocks, const std::unordered_set<BlockID> unique_block_ids, const int& chunk_size, const BlockManager& block_manager);

}