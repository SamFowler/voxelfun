#include "BlockMeshGenerator.hpp"

#include <vector>
#include <array>
#include <GL/glew.h>


#include <iostream> //temp

namespace BlockMeshGenerator 
{
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

    BlockMesh makeBlockMesh(const Block& block, const MeshMethod& mesh_method)
    {
        if (mesh_method == CULL_MESH_FAST) // doesn't check neighbouring chunks
            return makeBlockMesh_Culling(block);
        else if (mesh_method == CULL_MESH_OPTIMAL) // checks neighbouring chunks for voxel visibility
            return makeBlockMesh_Culling(block);
        else if (mesh_method == GREEDY_MESH)
            return makeBlockMesh_Greedy(block);
        else if (mesh_method == NAIVE_MESH)
            return makeBlockMesh_Naive(block);
        else if (mesh_method == OPTIMAL_MESH)
            return makeBlockMesh_Optimal(block);

        return makeBlockMesh_Culling(block);
    }

    bool isBlockEdge(const glm::ivec3& position, const int& size)
    {
        if (position.x == 0 || position.y == 0 || position.z == 0 || 
            (position.x + 1) == size || (position.y + 1) == size || (position.z + 1) == size)
            return true;
        return false;
    }

    int getVoxelIndex(const glm::ivec3& voxel_position, const int& size)
    {
        return (voxel_position.x) + (voxel_position.z * size) + (voxel_position.y * size * size);
    }

    std::array<bool, 6> getNeighbours(const glm::ivec3& vox_pos, const Block& block)
    {
        return {
            doesNeighbourExist({vox_pos.x - 1, vox_pos.y, vox_pos.z}, block),
            doesNeighbourExist({vox_pos.x + 1, vox_pos.y, vox_pos.z}, block),
            doesNeighbourExist({vox_pos.x, vox_pos.y - 1, vox_pos.z}, block),
            doesNeighbourExist({vox_pos.x, vox_pos.y + 1, vox_pos.z}, block),
            doesNeighbourExist({vox_pos.x, vox_pos.y, vox_pos.z - 1}, block),
            doesNeighbourExist({vox_pos.x, vox_pos.y, vox_pos.z + 1}, block)
        };        
    }

    std::array<bool, 6> getNeighbours_safe(const glm::ivec3& vox_pos, const Block& block) //, const Blocks& blocks)
    {
        int size = block.getSize();
        return {
            ( (vox_pos.x == 0)    ?     false : (doesNeighbourExist_safe({vox_pos.x - 1, vox_pos.y, vox_pos.z}, block)) ),
            ( (vox_pos.x + 1 == size) ? false : (doesNeighbourExist_safe({vox_pos.x + 1, vox_pos.y, vox_pos.z}, block)) ),
            ( (vox_pos.y == 0)    ?     false : (doesNeighbourExist_safe({vox_pos.x, vox_pos.y - 1, vox_pos.z}, block)) ),
            ( (vox_pos.y + 1 == size) ? false : (doesNeighbourExist_safe({vox_pos.x, vox_pos.y + 1, vox_pos.z}, block)) ),
            ( (vox_pos.z == 0)    ?     false : (doesNeighbourExist_safe({vox_pos.x, vox_pos.y, vox_pos.z - 1}, block)) ),
            ( (vox_pos.z + 1 == size) ? false : (doesNeighbourExist_safe({vox_pos.x, vox_pos.y, vox_pos.z + 1}, block)) )
        };
    }

    bool doesNeighbourExist(const glm::ivec3& neighbour_position, const Block& block)
    {
        if (block.getVoxel(getVoxelIndex(neighbour_position, block.getSize())) > 0) // TODO: yikes
            return true;

        return false;
    }

    bool doesNeighbourExist_safe(const glm::ivec3& neighbour_position, const Block& block)
    {
        //TODO: COMPLETE THIS FUNCTION: need to add checking for neighbouring blocks.
        //      Need to pass in some container of blocks and through that check whether voxel in neighbouring block exists
        return doesNeighbourExist(neighbour_position, block); // TODO: this is temp
    }

    void addFace(BlockMesh& mesh, const VertexData_i& face_verts, const glm::ivec3& voxel_pos, 
                                        int& element_count, const Colour& colour, const glm::vec3& normal)
    {
        //TODO: make this pack bits into a few bytes rather than large number of bytes for each vertex attribute
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.x);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.y);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.z);

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

    BlockMesh makeBlockMesh_Naive(const Block& block)
    {
        return BlockMesh(); // TODO: complete
    }

    BlockMesh makeBlockMesh_Culling(const Block& block)
    {

        BlockMesh block_mesh;

        int element_count = 0;
        int block_size = block.getSize();

        std::cout << block.getVoxel(0) << "," << block.getVoxel(1) << "," << block.getVoxel(2) << "," << block.getVoxel(3) << "," << std::endl;

        //TODO: change neigbours to a packed bit with bit mask flags rather than array of bools
        std::array<bool, 6> neighbours;

        for (int y = 0; y < block_size; y++)
        {
            for (int z = 0; z < block_size; z++)
            {
                for (int x = 0; x < block_size; x++)
                {
                    
                    glm::ivec3 voxel_pos = {x,y,z};
                    int voxel_index = getVoxelIndex(voxel_pos, block_size);

                    VoxelID voxel_id = block.getVoxel(voxel_index);
                    
                    if (voxel_id <= 0)
                        continue;
                    
                    Colour voxel_colour = block.getColour(voxel_id - 1); // (voxel_id - 1) as there is no colour for empty block
                    
                    if (isBlockEdge(voxel_pos, block_size))
                        neighbours = getNeighbours_safe(voxel_pos, block); //TODO: _safe function is not properly implemented yet
                    else 
                        neighbours = getNeighbours(voxel_pos, block); 

                    if (neighbours[0] == false) // if x-1 neighbour doesn't exists, draw face
                        addFace(block_mesh, X_MINUS_FACE, voxel_pos, element_count, voxel_colour, X_MINUS_NORMAL);
                    if (neighbours[1] == false) // if x+1 neighbour doesn't exists, draw face
                        addFace(block_mesh, X_PLUS_FACE, voxel_pos, element_count, voxel_colour, X_PLUS_NORMAL);
                    if (neighbours[2] == false) // if y-1 neighbour doesn't exists, draw face
                        addFace(block_mesh, Y_MINUS_FACE, voxel_pos, element_count, voxel_colour, Y_MINUS_NORMAL);
                    if (neighbours[3] == false) // if y+1 neighbour doesn't exists, draw face
                        addFace(block_mesh, Y_PLUS_FACE, voxel_pos, element_count, voxel_colour, Y_PLUS_NORMAL);
                    if (neighbours[4] == false) // if z-1 neighbour doesn't exists, draw face
                        addFace(block_mesh, Z_MINUS_FACE, voxel_pos, element_count, voxel_colour, Z_MINUS_NORMAL);
                    if (neighbours[5] == false) // if z+1 neighbour doesn't exists, draw face
                        addFace(block_mesh, Z_PLUS_FACE, voxel_pos, element_count, voxel_colour, Z_PLUS_NORMAL);
                    
                } //x loop
            } //z loop
        } //y loop

        return block_mesh;
    }
    
    BlockMesh makeBlockMesh_Greedy(const Block& block)
    {
        return BlockMesh(); // TODO: complete
    }

    BlockMesh makeBlockMesh_Optimal(const Block& block)
    {
        return BlockMesh(); // TODO: complete
    }


} //BlockMeshGenerator namespace