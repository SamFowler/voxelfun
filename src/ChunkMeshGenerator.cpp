#include "ChunkMeshGenerator.hpp"
#include <iostream>

namespace ChunkMeshGenerator {


    //TODO: in future use GLbyte for vertex data for optimisation, and bit pack different vertex data into same VBO 
    using VertexData_i = std::vector<GLuint>;
    using VertexData_f = std::vector<GLfloat>;

    const VertexData_i X_MINUS_FACE = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0};
    const VertexData_i Y_MINUS_FACE = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1};
    const VertexData_i Z_MINUS_FACE = {0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    const VertexData_i X_PLUS_FACE =  {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1};
    const VertexData_i Y_PLUS_FACE =  {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
    const VertexData_i Z_PLUS_FACE =  {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1};

    const glm::vec3 X_MINUS_NORMAL = {-1.0f, 0.0f, 0.0f};
    const glm::vec3 Y_MINUS_NORMAL = {0.0f, -1.0f, 0.0f};
    const glm::vec3 Z_MINUS_NORMAL = {0.0f, 0.0f, -1.0f};
    const glm::vec3 X_PLUS_NORMAL =  {1.0f, 0.0f, 0.0f};
    const glm::vec3 Y_PLUS_NORMAL =  {0.0f, 1.0f, 0.0f};
    const glm::vec3 Z_PLUS_NORMAL =  {0.0f, 0.0f, 1.0f};

void addFace(Mesh& mesh, const VertexData_i& face_verts, const glm::ivec3& block_plus_voxel_pos, 
                                        int& element_count, const Colour& colour, const glm::vec3& normal)
    {
        //TODO: make this pack bits into a few bytes rather than large number of bytes for each vertex attribute
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(face_verts[index++] + block_plus_voxel_pos.x);
            mesh.vertices.push_back(face_verts[index++] + block_plus_voxel_pos.y);
            mesh.vertices.push_back(face_verts[index++] + block_plus_voxel_pos.z);

            mesh.colours.push_back(colour.r);
            mesh.colours.push_back(colour.g);
            mesh.colours.push_back(colour.b);

            mesh.normals.push_back(normal.x);
            mesh.normals.push_back(normal.y);
            mesh.normals.push_back(normal.z);
        }

        // add elements for two polygons representing the voxel face
        mesh.elements.push_back(element_count);
        mesh.elements.push_back(element_count + 1);
        mesh.elements.push_back(element_count + 2);

        mesh.elements.push_back(element_count + 2);
        mesh.elements.push_back(element_count + 3);
        mesh.elements.push_back(element_count);
        element_count += 4;
    }


    void addBlockToMesh(const Block* block, Mesh& chunk_mesh, int& element_count, const glm::ivec3& block_pos)
    {
                   
        //std::cout << "adding block pos: " << block_pos.x << ", " << block_pos.y << ", " << block_pos.z << std::endl;
        int block_size = block->getSize();

        for (int y = 0; y < block_size; y++)
        {
            for (int z = 0; z < block_size; z++)
            {
                for (int x = 0; x < block_size; x++)
                {
                    glm::ivec3 voxel_pos = {x,y,z};
                    int voxel_index = voxel_pos.x + voxel_pos.z*block_size + voxel_pos.y*block_size*block_size;

                    VoxelID voxel_id = block->getVoxel(voxel_index);
                    
                    if (voxel_id <= 0)
                        continue;
                    
                    Colour voxel_colour = block->getColour(voxel_id - 1); // (voxel_id - 1) as there is no colour for empty block
                    
                    char neighbours = block->getNeighbours(voxel_pos);
                    glm::ivec3 block_plus_voxel_pos = voxel_pos + block_pos;

                    if ( (neighbours & 0x01 ) == 0 ) // if x-1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, X_MINUS_FACE, block_plus_voxel_pos, element_count, voxel_colour, X_MINUS_NORMAL);
                    if ( (neighbours & 0x02 ) == 0 ) // if x+1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, X_PLUS_FACE, block_plus_voxel_pos, element_count, voxel_colour, X_PLUS_NORMAL);
                    if ( (neighbours & 0x04 ) == 0 ) // if y-1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Y_MINUS_FACE, block_plus_voxel_pos, element_count, voxel_colour, Y_MINUS_NORMAL);
                    if ( (neighbours & 0x08 ) == 0 ) // if y+1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Y_PLUS_FACE, block_plus_voxel_pos, element_count, voxel_colour, Y_PLUS_NORMAL);
                    if ( (neighbours & 0x10 ) == 0 ) // if z-1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Z_MINUS_FACE, block_plus_voxel_pos, element_count, voxel_colour, Z_MINUS_NORMAL);
                    if ( (neighbours & 0x20 ) == 0 ) // if z+1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Z_PLUS_FACE, block_plus_voxel_pos, element_count, voxel_colour, Z_PLUS_NORMAL);
                    
                } //x loop
            }//z loop
        }//y loop

    }

    Mesh makeChunkMesh_Culling(const std::vector<BlockID>& blocks, const std::unordered_set<BlockID> unique_block_ids,
                                const int& chunk_size,
                                const BlockManager& block_manager)
                          
    {

        std::unordered_map<BlockID, const Block*> unique_blocks;

        for (const BlockID& id : unique_block_ids)
        {
            unique_blocks.emplace(id, block_manager.getBlock(id));
        }

        Mesh chunk_mesh;

        int c_size = chunk_size;
        int element_count = 0;

        for (int y = 0; y < c_size; y++)
        {
            for (int z = 0; z < c_size; z++)
            {
                for (int x = 0; x < c_size; x++)
                {
                    glm::ivec3 block_pos = {x,y,z};
                    
                    int block_index = block_pos.x + (block_pos.z * c_size) + (block_pos.y * c_size * c_size);
                    BlockID block_id = blocks[block_index];

                    if (block_id <= 0)
                        continue;

                    const Block* block_ptr = unique_blocks[block_id];

                    addBlockToMesh(block_ptr, chunk_mesh, element_count, block_pos);
                    std::cout << "num_verts:" << chunk_mesh.vertices.size() << std::endl;
                } //x loop
            } //z loop
        } //y loop    


        return chunk_mesh;    


/*
                    
                    if (voxel_id <= 0)
                        continue;
                    
                    Colour voxel_colour = block.getColour(voxel_id - 1); // (voxel_id - 1) as there is no colour for empty block
                    
                    char neighbours = block.getNeighbours(voxel_pos);
                    
                    if ( ( (neighbours >> 0) * 1U) == 0 ) // if x-1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, X_MINUS_FACE, voxel_pos, element_count, voxel_colour, X_MINUS_NORMAL);
                    if ( ( (neighbours >> 1) * 1U) == 0 ) // if x+1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, X_PLUS_FACE, voxel_pos, element_count, voxel_colour, X_PLUS_NORMAL);
                    if ( ( (neighbours >> 2) * 1U) == 0 ) // if y-1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Y_MINUS_FACE, voxel_pos, element_count, voxel_colour, Y_MINUS_NORMAL);
                    if ( ( (neighbours >> 3) * 1U) == 0 ) // if y+1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Y_PLUS_FACE, voxel_pos, element_count, voxel_colour, Y_PLUS_NORMAL);
                    if ( ( (neighbours >> 4) * 1U) == 0 ) // if z-1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Z_MINUS_FACE, voxel_pos, element_count, voxel_colour, Z_MINUS_NORMAL);
                    if ( ( (neighbours >> 5) * 1U) == 0 ) // if z+1 neighbour doesn't exists, draw face
                        addFace(chunk_mesh, Z_PLUS_FACE, voxel_pos, element_count, voxel_colour, Z_PLUS_NORMAL);
                    
                } //x loop
            }//z loop
        }//y loop
*/
    }


}//namespace