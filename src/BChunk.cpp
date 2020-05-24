#include "BChunk.hpp"

#include <map>
#include <iostream>
#include <valarray>

#include "ChunkMeshGenerator.hpp"

Mesh BChunk::makeMesh(const BlockManager& block_manager) const
{

    //return ChunkMeshGenerator::makeChunkMesh_Culling(m_blocks, m_unique_blocks, m_size, block_manager);
    /*
    Mesh chunk_mesh; 
    //TODO get list of block ids within the chunk
    std::map<BlockID, Mesh> block_meshes;
    std::cout << "chunk making mesh" << std::endl;
    


    for (const BlockID& id : m_unique_blocks)
    {
        block_meshes.emplace(id, mesh_manager.getMesh(id));
    }
    std::valarray<unsigned int> vert_valarr(block_meshes[1].vertices.data(), block_meshes[1].vertices.size());

    
    
    for (auto block_id : m_blocks)
    {
        //Mesh block_mesh = mesh_manager.getMeshRef(block_id);
        Mesh this_block_mesh = block_meshes[block_id];
        for (auto it : this_block_mesh.vertices)
        {
            std::cout << it << std::endl;
        }
        std::cout << "block mesh end" << std::endl << std::endl;
    }
    
    return chunk_mesh;

    */
    
}