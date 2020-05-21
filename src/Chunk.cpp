#include "Chunk.hpp"

#include <iostream>

Chunk::Chunk(pos3d position, const int& side_size)
 : m_position(position), m_side(side_size), m_side_sq(side_size * side_size), m_volume(side_size * side_size * side_size), m_voxels(m_volume, BLOCK)
{

}

voxel_type Chunk::getVoxelType(const pos3d& position)
{
    return m_voxels[getVoxelIndex(position)];
}

bool Chunk::isVoxelThere(const pos3d& position)
{
    if (getVoxelType(position) == AIR)
        return false;

    return true;
}


int Chunk::getVoxelIndex(const pos3d& voxel_position)
{
    return (voxel_position.x) + (voxel_position.z * m_side) + (voxel_position.y * m_side_sq);
}

 void Chunk::makeChunkMesh()
 {

    std::vector<GLuint> verts = {
        0, 0, 1, 
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0
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
    
    std::vector<GLuint> wire_cube_elements = {
        1, 0, 4,
        4, 7, 6,
        6, 5, 4,
        4, 5, 1,

        1, 5, 6, 
        6, 2, 1,

        1, 2, 3,
        3, 2, 6,
        6, 7, 3,
        3, 7, 4,
        4, 0, 3,
        3, 0, 1


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

    };

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
                        m_mesh.elements.push_back(wire_cube_elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(wire_cube_elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(wire_cube_elements[index++] + (voxel_index*8));

                        m_mesh.elements.push_back(wire_cube_elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(wire_cube_elements[index++] + (voxel_index*8));
                        m_mesh.elements.push_back(wire_cube_elements[index++] + (voxel_index*8));
                    }
                }
            }
        }
     }
 }


void Chunk::addFace(const std::vector<GLuint>& faceVerts, const pos3d& voxelPos, int& element_count, const colour& col)
{
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        m_mesh.vertices.push_back(faceVerts[index++] + voxelPos.x);
        m_mesh.vertices.push_back(faceVerts[index++] + voxelPos.y);
        m_mesh.vertices.push_back(faceVerts[index++] + voxelPos.z);

        m_mesh.colours.push_back(col.r);
        m_mesh.colours.push_back(col.g);
        m_mesh.colours.push_back(col.b);
    }


    
    // add elements for two polygons representing the voxel face
    m_mesh.elements.push_back(element_count);
    m_mesh.elements.push_back(element_count + 1);
    m_mesh.elements.push_back(element_count + 2);

    m_mesh.elements.push_back(element_count + 2);
    m_mesh.elements.push_back(element_count + 3);
    m_mesh.elements.push_back(element_count);
    element_count += 4;
}

void Chunk::makeEfficientChunkMesh()
{
     /*
    std::vector<GLuint> verts = {
        0, 0, 1, 
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0
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
    };

    std::vector<GLuint> elements = {
        0, 0, 1, 0, 1, 1, 0, 1, 0,
        0, 1, 0, 1, 1, 0, 1, 0, 0,

        1, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 1,

        0, 0, 1, 0, 0, 0, 1, 0, 0,
        1, 0, 0, 1, 1, 0, 1, 1, 1,

        1, 1, 1, 1, 0, 1, 1, 0, 0,
        1, 0, 0, 1, 0, 1, 0, 0, 1,

        0, 0, 1, 1, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 0, 0, 1, 0,

        0, 1, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 0, 0, 1
    };

    std::vector<std::vector<GLuint>> verts2 = 
    {
        {0, 0, 1}, 
        {1, 0, 1},
        {1, 1, 1},
        {0, 1, 1},
        {0, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0}
    };
    */

    std::vector<GLuint> xMinusFace = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0};
    std::vector<GLuint> yMinusFace = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1};
    std::vector<GLuint> zMinusFace = {0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    std::vector<GLuint> xPlusFace =  {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1};
    std::vector<GLuint> yPlusFace =  {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
    std::vector<GLuint> zPlusFace =  {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1};

/*
    std::vector<GLuint> elements2 = {
        //x-1
        0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0,
        //y-1
        0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1,
        //z-1
        0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0,
        //x+1
        1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
        //y+1
        1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1,
        //z+1
        1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1,
    };*/


    int element_count = 0;

    for (int y = 0; y < m_side; y++)
    {
        for (int z = 0; z < m_side; z++)
        {
            std::cout << std::endl;
            for (int x = 0; x < m_side; x++)
            {
                pos3d voxelPos = {x, y, z};
                int voxel_index = getVoxelIndex(voxelPos);
                voxel_type type = m_voxels[voxel_index];

                if (getVoxelType(voxelPos) == BLOCK)
                {
                    if (x == 0 || y == 0 || z == 0 || x+1 == m_side || y+1 == m_side || z+1 == m_side)
                    {
                        //draw voxel as on edge of the chunk
                        addFace(xMinusFace, voxelPos, element_count, {0.4, 0.0, 0.0});
                        addFace(xPlusFace, voxelPos, element_count, {1.0, 0.0, 0.0});
                        addFace(yMinusFace, voxelPos, element_count, {0.0, 0.4, 0.0});
                        addFace(yPlusFace, voxelPos, element_count, {0.0, 1.0, 0.0});
                        addFace(zMinusFace, voxelPos, element_count, {0.0, 0.0, 0.4});
                        addFace(zPlusFace, voxelPos, element_count, {0.0, 0.0, 1.0});

                        //TODO: in future check to see if edge voxels are obscured by neighbouring chunks, and so do not need to be drawn
                    }
                    else 
                    {
                        //check to see if voxel is surrounded by other "full" voxels
                        if (!isVoxelThere({x-1, y, z}))
                        {
                            addFace(xMinusFace, voxelPos, element_count, {0.4, 0.0, 0.0});
                        }
                        if (!isVoxelThere({x+1, y, z}))
                        {
                            //draw x+1 face
                            addFace(xPlusFace, voxelPos, element_count, {1.0, 0.0, 0.0});
                        }
                        if (!isVoxelThere({x, y-1, z}))
                        {
                            //draw y-1 face
                            addFace(yMinusFace, voxelPos, element_count, {0.0, 0.4, 0.0});
                        }
                        if (!isVoxelThere({x, y+1, z}))
                        {
                            addFace(yPlusFace, voxelPos, element_count, {0.0, 1.0, 0.0});
                        }
                        if (!isVoxelThere({x, y, z-1}))
                        {
                            addFace(zMinusFace, voxelPos, element_count, {0.0, 0.0, 0.4});
                        }
                        if (!isVoxelThere({x, y, z+1}))
                        {
                            addFace(zPlusFace, voxelPos, element_count, {0.0, 0.0, 1.0});
                        }
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
    //vao.addVertexBuffer(3, m_mesh.vertices);
    vao.addVertexBuffer(3, m_mesh.vertices);
    vao.addVertexBuffer(3, m_mesh.colours);
    vao.addElementBuffer(m_mesh.elements);
    return vao;
 }