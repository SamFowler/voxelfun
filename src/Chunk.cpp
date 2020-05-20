#include "Chunk.hpp"

#include <iostream>

Chunk::Chunk(pos3d position, const int& side_size)
 : m_position(position), m_side(side_size), m_side_sq(side_size * side_size), m_volume(side_size * side_size * side_size), m_voxels(m_volume, BLOCK)
{

}

int Chunk::getVoxelIndex(const pos3d& voxel_position)
{
    return (voxel_position.x) + (voxel_position.z * m_side) + (voxel_position.y * m_side_sq);
}

 void Chunk::makeChunkMesh()
 {
     std::vector<GLfloat> verts = {
        //front
        -0.5f, -0.5f, 0.5f, // 0
         0.5f, -0.5f, 0.5f, // 1
         0.5f,  0.5f, 0.5f, // 2
        -0.5f,  0.5f, 0.5f, // 3

        //back
        -0.5f, -0.5f, -0.5f, // 4
         0.5f, -0.5f, -0.5f, // 5
         0.5f,  0.5f, -0.5f, // 6
        -0.5f,  0.5f, -0.5f, // 7
    };

     std::vector<GLfloat> colours = {
        //front colours
        1.0f, 0.0f, 0.0f, // 0
        0.0f, 1.0f, 0.0f, // 1
        0.0f, 0.0f, 1.0f, // 2
        1.0f, 1.0f, 1.0f, // 3
        //back colours
        1.0f, 1.0f, 0.0f, // 4
        0.0f, 1.0f, 1.0f, // 5
        1.0f, 0.0f, 1.0f, // 6
        0.0f, 0.0f, 0.0f, // 7
    };
    
    std::vector<GLuint> elements = {
        0, 3, 7,
        7, 6, 5,

        5, 4, 7,
        7, 4, 0,

        0, 4, 5,
        5, 6, 2,

        2, 1, 5,
        5, 1, 0,

        0, 1, 2,
        2, 6, 7,

        7, 3, 2,
        2, 3, 0




        
        /*
        //front
        0, 1, 2,
        2, 3, 0,
        //right
        1, 5, 6,
        6, 2, 1,
        //back 
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        //bottom
        4, 5, 1,
        1, 0, 4,
        //top
        //3, 2, 6,
        //6, 7, 3,
        7, 3, 2,
        2, 6, 7
        */
    };
     /*
     std::vector<GLuint> cube_verts = {
        0, 0, 0, 
        0, 0, 1,
        0, 1, 0,
        0, 1, 1,

        1, 0, 0,
        1, 0, 1,
        1, 1, 0,
        1, 1, 1
    };

    std::vector<GLuint> cube_elements = {
        //front
        0, 1, 3,
        3, 2, 0,
        //right
        4, 0, 2,
        2, 6, 4,
        //back 
        5, 4, 6,
        6, 7, 5,
        // left
        1, 2, 7,
        7, 3, 1,
        //bottom
        0, 4, 5,
        5, 1, 0,
        //top
        2, 3, 7,
        7, 7, 2
    };
    */

     for (int y = 0; y < m_side; y++)
     {
         for (int z = 0; z < m_side; z++)
        {
            for (int x = 0; x < m_side; x++)
            {

                int voxel_index = getVoxelIndex({x,y,z});
                voxel_type type = m_voxels[voxel_index];

                if (type == BLOCK)
                {
                    
                    //add vertex position data of each cube vertices to mesh vertex vector
                    int index = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        m_mesh.vertices.push_back(verts[index++] + x);
                        m_mesh.vertices.push_back(verts[index++] + y);
                        m_mesh.vertices.push_back(verts[index++] + z);
                    }

                    index = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        m_mesh.colours.push_back(colours[index++]);
                        m_mesh.colours.push_back(colours[index++]);
                        m_mesh.colours.push_back(colours[index++]);
                    }

                    //add cube elements to mesh elements vector
                    index = 0;
                    
                    for (int i = 0; i < 6; i++)
                    {   
                        //add elements for a specific face of the cube
                        m_mesh.elements.push_back(elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(elements[index++] + (voxel_index*8));

                        m_mesh.elements.push_back(elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(elements[index++] + (voxel_index*8));
                    }
                }
            }
        }
     }
 }

 VertexArrayObject Chunk::createVao()
 {
    std::cout << "creating chunk VAO with numverts " << m_mesh.vertices.size() << " and numElements " << m_mesh.elements.size() << std::endl;
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, m_mesh.vertices);
    vao.addVertexBuffer(3, m_mesh.colours);
    vao.addElementBuffer(m_mesh.elements);
    return vao;
 }