#include "ChunkMeshGenerator.h"

#include <iostream>

namespace ChunkMeshGenerator
{

VertexArrayObject makeChunkVAO(const Chunk& chunk, const int& chunk_size, const MeshMethod& mesh_method)
{
    ChunkMesh chunk_mesh;
    if (mesh_method == CULL_MESH_FAST) // doesn't check neighbouring chunks
        makeChunkMesh_Culling(chunk, chunk_size, chunk_mesh);
    else if (mesh_method == CULL_MESH_OPTIMAL) // checks neighbouring chunks for voxel visibility
        makeChunkMesh_Culling(chunk, chunk_size, chunk_mesh);
    else if (mesh_method == GREEDY_MESH)
        makeChunkMesh_Greedy(chunk, chunk_size ,chunk_mesh);
    else if (mesh_method == NAIVE_MESH)
        makeChunkMesh_Naive(chunk,chunk_size , chunk_mesh);
    else if (mesh_method == OPTIMAL_MESH)
        makeChunkMesh_Optimal(chunk, chunk_size, chunk_mesh);
    else 
        makeChunkMesh_Culling(chunk,chunk_size, chunk_mesh);

    return chunk_mesh.createChunkBuffer();
}

void makeChunkMesh_Naive  (const Chunk& chunk, const int& chunk_size, ChunkMesh& chunk_mesh)
{

}

void makeChunkMesh_Culling(const Chunk& chunk, const int& chunk_size, ChunkMesh& chunk_mesh)
{
    int element_count = 0;
    //int chunk_size = 8;
    for (unsigned int y = 0; y < chunk_size; y++)
    {
        for (unsigned int z = 0; z < chunk_size; z++)
        {
            for (unsigned int x = 0; x < chunk_size; x++)
            {
                VoxelInChunkPos voxel_pos = {x,y,z};
                
                unsigned int voxel_index = chunk.indexFromInChunkPos( voxel_pos );

                Voxel voxel = chunk.getVoxel( voxel_pos );

                Colour voxel_colour = chunk.getColour(voxel.getColourId());

                //if (voxel.hasXMinusNeighbour())
                    addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, X_MINUS_FACE, X_MINUS_NORMAL_INDEX);
                //if (voxel.hasXPlusNeighbour())
                    addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, X_PLUS_FACE, X_PLUS_NORMAL_INDEX);
                //if (voxel.hasYMinusNeighbour())
                    addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Y_MINUS_FACE, Y_MINUS_NORMAL_INDEX);
                //if (voxel.hasYPlusNeighbour())
                    addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Y_PLUS_FACE, Y_PLUS_NORMAL_INDEX);
                //if (voxel.hasZMinusNeighbour())
                    addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Z_MINUS_FACE, Z_MINUS_NORMAL_INDEX);
                //if (voxel.hasZPlusNeighbour())
                    addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Z_PLUS_FACE, Z_PLUS_NORMAL_INDEX);
            }
        }
    }

}

void makeChunkMesh_Greedy (const Chunk& chunk, const int& chunk_size, ChunkMesh& chunk_mesh)
{

}

void makeChunkMesh_Optimal(const Chunk& chunk, const int& chunk_size, ChunkMesh& chunk_mesh)
{

}



void addFace(ChunkMesh& mesh, const Voxel& voxel, const VoxelInChunkPos& voxel_pos, const Colour& voxel_colour,
                                 int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index)
{

        //TODO: make this pack bits into a few bytes rather than large number of bytes for each vertex attribute
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.pos.x);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.pos.y);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.pos.z);

            mesh.colours.push_back(voxel_colour.r/255.0f);
            mesh.colours.push_back(voxel_colour.g/255.0f);
            mesh.colours.push_back(voxel_colour.b/255.0f);
            mesh.colours.push_back(voxel_colour.a/255.0f);

            mesh.normals.push_back(normal_index);          
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


}