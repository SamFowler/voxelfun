#include "Chunk.hpp"

#include <iostream>



Chunk::Chunk(glm::vec3 position, const int& side_size)
 : m_position(position), m_side(side_size), m_side_sq(side_size * side_size), m_volume(side_size * side_size * side_size), m_voxels(m_volume, BLOCK)
{
std::cout << "chunk created" << std::endl;
}

 VertexArrayObject Chunk::getInitialVao()
 {
    VertexArrayObject vao;
    vao.create();
    return vao;
 }

void Chunk::changeVoxel(const glm::ivec3& position, const voxel_type type)
{
    //TODO: may be worth having a "safe" and "not-safe" version of this, where the check isn't made
    //      to improve performance if it can be guaranteed that position is always within the voxel
    if (getVoxelIndex(position) < m_volume)
    {
        m_voxels[getVoxelIndex(position)] = type;
    }
}

void Chunk::removeVoxel(const glm::ivec3& position)
{
    changeVoxel(position, AIR);
}


voxel_type Chunk::getVoxelType(const glm::ivec3& position)
{
    return m_voxels[getVoxelIndex(position)];
}

bool Chunk::isVoxelThere(const glm::ivec3& position)
{
    if (getVoxelType(position) == AIR)
        return false;

    return true;
}
bool Chunk::isVoxelThere_Safe(const glm::ivec3& position)
{
    if (isOutsideChunk(position))
    {
        return false;
        //TODO: in future should check if voxel in neighbouring chunk is present?
    }
    if (getVoxelType(position) == AIR)
        return false;

    return true;
}


bool Chunk::isOutsideChunk(const glm::ivec3& position)
{
    if (position.x < 0 || position.y < 0 || position.z < 0 || position.x == m_side || position.y == m_side || position.z == m_side)
        return true;
    return false;

}


bool Chunk::isChunkEdge(const glm::ivec3& position)
{
    if (position.x == 0 || position.y == 0 || position.z == 0 || (position.x + 1) == m_side || (position.y + 1) == m_side || (position.z + 1) == m_side)
        return true;
    return false;
}



int Chunk::getVoxelIndex(const glm::ivec3& voxel_position)
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


void Chunk::addFace(const std::vector<GLuint>& faceVerts, const glm::ivec3& voxelPos, int& element_count, const glm::vec3& col)
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
            for (int x = 0; x < m_side; x++)
            {
                glm::ivec3 voxelPos = {x, y, z};
                int voxel_index = getVoxelIndex(voxelPos);
                voxel_type type = m_voxels[voxel_index];

                
                if (getVoxelType(voxelPos) == BLOCK)
                {
                    /*
                    if (x == 0 || y == 0 || z == 0)
                    {
                        if (!isVoxelThere({x+1, y, z}))
                        {
                            addFace(xPlusFace, voxelPos, element_count, {1.0, 0.0, 0.0});
                        }
                        if (!isVoxelThere({x, y+1, z}))
                        {
                            addFace(yPlusFace, voxelPos, element_count, {0.0, 0.0, 0.4});
                        }
                        if (!isVoxelThere({x, y, z+1}))
                        {
                            addFace(zPlusFace, voxelPos, element_count, {0.0, 0.0, 1.0});
                        }
                    }
                    
                    if (x+1 == m_side || y+1 == m_side || z+1 == m_side)
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
                    */
                    //else 
                    
                        //check to see if voxel is surrounded by other "full" voxels
                        /*
                    if (!isChunkEdge(position.x))
                    {
                        if ( !isVoxelThere({x-1, y, z}))
                        {
                            addFace(xMinusFace, voxelPos, element_count, {0.4, 0.0, 0.0});
                        }
                        if (!isVoxelThere({x+1, y, z}))
                        {
                            //draw x+1 face
                            addFace(xPlusFace, voxelPos, element_count, {1.0, 0.0, 0.0});
                        }
                    }
                    else 
                    {
                        if (position.x == 0)
                        {
                            addFace(xMinusFace, voxelPos, element_count, {0.4, 0.0, 0.0});
                            if (!isVoxelThere({x+1, y, z}))
                            {
                                addFace(xPlusFace, voxelPos, element_count, {1.0, 0.0, 0.0});
                            }
                        }
                            
                        if ( (position.x + 1) == m_side )
                    */
                    if (isChunkEdge({x, y, z}))
                    {
                        if (!isVoxelThere_Safe({x-1, y, z}))
                        {
                            addFace(xMinusFace, voxelPos, element_count, {0.4, 0., 0.0});
                        }
                        if (!isVoxelThere_Safe({x+1, y, z}))
                        {
                            addFace(xPlusFace, voxelPos, element_count, {1.0, 0.0, 0.0});
                        }
                        if (!isVoxelThere_Safe({x, y-1, z}))
                        {
                            //draw y-1 face
                            addFace(yMinusFace, voxelPos, element_count, {0.0, 0.4, 0.0});
                        }
                        if (!isVoxelThere_Safe({x, y+1, z}))
                        {
                            addFace(yPlusFace, voxelPos, element_count, {0.0, 1.0, 0.0});
                        }
                        if (!isVoxelThere_Safe({x, y, z-1}))
                        {
                            addFace(zMinusFace, voxelPos, element_count, {0.0, 0.0, 0.4});
                        }
                        if (!isVoxelThere_Safe({x, y, z+1}))
                        {
                            addFace(zPlusFace, voxelPos, element_count, {0.0, 0.0, 1.0});
                        }
                    }
                    else
                    {
                        if (!isVoxelThere({x-1, y, z}))
                        {
                            addFace(xMinusFace, voxelPos, element_count, {0.4, 0.0, 0.0});
                        }
                        if (!isVoxelThere({x+1, y, z}))
                        {
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


/*
 void Chunk::createVao()
 {
    std::cout << "creating chunk VAO with numverts " << m_mesh.vertices.size() << " and numElements " << m_mesh.elements.size() << std::endl;
    //VertexArrayObject vao;
    //m_vao.create();
    m_vao.bind();
    //vao.addVertexBuffer(3, m_mesh.vertices);
    m_vao.addVertexBuffer(3, m_mesh.vertices);
    m_vao.addVertexBuffer(3, m_mesh.colours);
    m_vao.addElementBuffer(m_mesh.elements);
    //return vao;
 }

 void Chunk::bindAndDraw()
 {
     m_vao.getDrawable().bindAndDraw();
 }
 */


VertexArrayObject Chunk::createAndGetVao()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, m_mesh.vertices);
    vao.addVertexBuffer(3, m_mesh.colours);
    vao.addElementBuffer(m_mesh.elements);
    return vao;
}

ChunkRenderable Chunk::getChunkRenderable()
{
    /*
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, m_mesh.vertices);
    vao.addVertexBuffer(3, m_mesh.colours);
    vao.addElementBuffer(m_mesh.elements);
    return {vao, m_position};
    */
}