#include "Chunk.hpp"

#include <iostream>

Chunk::Chunk(const glm::vec3 position, const int side_size)
 : m_position(position), m_side(side_size), m_side_sq(side_size * side_size), m_volume(side_size * side_size * side_size), 
    m_voxels(m_volume, 1)
{
    std::cout << "chunk created" << std::endl;
    m_colours.push_back({1.0f, 0.0f, 1.0f});
}

Chunk::Chunk(const glm::vec3 position, const std::vector<glm::vec3> colours, const int side_size)
 : m_position(position), m_side(side_size), m_side_sq(side_size * side_size), 
    m_volume(side_size * side_size * side_size), m_colours(colours)//, m_voxels(m_volume, BLOCK)
{
    for (int i = 0; i < m_volume; i ++)
    {
        int vox = (rand() % 4);
        m_voxels.push_back(vox);
    }
}

 VertexArrayObject Chunk::getInitialVao()
 {
    VertexArrayObject vao;
    vao.create();
    return vao;
 }

void Chunk::changeVoxel(const glm::ivec3& position, const unsigned int type)
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
    changeVoxel(position, 0);
}

unsigned int Chunk::getVoxelType(const glm::ivec3& position)
{
    return m_voxels[getVoxelIndex(position)];
}

bool Chunk::isVoxelThere(const glm::ivec3& position)
{
    if (getVoxelType(position) == 0)
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
    if (getVoxelType(position) == 0)
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
                unsigned int type = m_voxels[voxel_index];

                if (type != 0)
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

void Chunk::addFace(const std::vector<GLuint>& faceVerts, const glm::ivec3& voxelPos, int& element_count, const glm::vec3& col, const glm::vec3& normal)
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

        m_mesh.normals.push_back(normal.x);
        m_mesh.normals.push_back(normal.y);
        m_mesh.normals.push_back(normal.z);
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
    std::vector<GLuint> xMinusFace = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0};
    std::vector<GLuint> yMinusFace = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1};
    std::vector<GLuint> zMinusFace = {0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    std::vector<GLuint> xPlusFace =  {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1};
    std::vector<GLuint> yPlusFace =  {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
    std::vector<GLuint> zPlusFace =  {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1};


    int element_count = 0;

    for (int y = 0; y < m_side; y++)
    {
        for (int z = 0; z < m_side; z++)
        {
            for (int x = 0; x < m_side; x++)
            {
                glm::ivec3 voxelPos = {x, y, z};
                int voxel_index = getVoxelIndex(voxelPos);
                unsigned int type = m_voxels[voxel_index];

                
                if (getVoxelType(voxelPos) != 0)
                {
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

 void Chunk::makeColouredEfficientChunkMesh()
{
    std::vector<GLuint> xMinusFace = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0};
    std::vector<GLuint> yMinusFace = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1};
    std::vector<GLuint> zMinusFace = {0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
    std::vector<GLuint> xPlusFace =  {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1};
    std::vector<GLuint> yPlusFace =  {1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
    std::vector<GLuint> zPlusFace =  {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1};

    glm::vec3 xMinusNormal = {-1.0f, 0.0f, 0.0f};
    glm::vec3 yMinusNormal = {0.0f, -1.0f, 0.0f};
    glm::vec3 zMinusNormal = {0.0f, 0.0f, -1.0f};
    glm::vec3 xPlusNormal =  {1.0f, 0.0f, 0.0f};
    glm::vec3 yPlusNormal =  {0.0f, 1.0f, 0.0f};
    glm::vec3 zPlusNormal =  {0.0f, 0.0f, 1.0f};

    int element_count = 0;

    for (int y = 0; y < m_side; y++)
    {
        for (int z = 0; z < m_side; z++)
        {
            for (int x = 0; x < m_side; x++)
            {
                glm::ivec3 voxelPos = {x, y, z};
                int voxel_index = getVoxelIndex(voxelPos);

                unsigned int type = getVoxelType(voxelPos);
                unsigned int colour_ind = type - 1;
                if (type != 0)
                {
                    if (isChunkEdge({x, y, z}))
                    {
                        if (!isVoxelThere_Safe({x-1, y, z}))
                        {
                            addFace(xMinusFace, voxelPos, element_count, m_colours[colour_ind], xMinusNormal);
                        }
                        if (!isVoxelThere_Safe({x+1, y, z}))
                        {
                            addFace(xPlusFace, voxelPos, element_count, m_colours[colour_ind], xPlusNormal);
                        }
                        if (!isVoxelThere_Safe({x, y-1, z}))
                        {
                            addFace(yMinusFace, voxelPos, element_count, m_colours[colour_ind], yMinusNormal);
                        }
                        if (!isVoxelThere_Safe({x, y+1, z}))
                        {
                            addFace(yPlusFace, voxelPos, element_count, m_colours[colour_ind], yPlusNormal);
                        }
                        if (!isVoxelThere_Safe({x, y, z-1}))
                        {
                            addFace(zMinusFace, voxelPos, element_count, m_colours[colour_ind], zMinusNormal);
                        }
                        if (!isVoxelThere_Safe({x, y, z+1}))
                        {
                            addFace(zPlusFace, voxelPos, element_count, m_colours[colour_ind], zPlusNormal);
                        }
                    }
                    else
                    {
                        if (!isVoxelThere({x-1, y, z}))
                        {
                            addFace(xMinusFace, voxelPos, element_count, m_colours[colour_ind], xMinusNormal);
                        }
                        if (!isVoxelThere({x+1, y, z}))
                        {
                            addFace(xPlusFace, voxelPos, element_count, m_colours[colour_ind], xPlusNormal);
                        }
                        if (!isVoxelThere({x, y-1, z}))
                        {
                            addFace(yMinusFace, voxelPos, element_count, m_colours[colour_ind], yMinusNormal);
                        }
                        if (!isVoxelThere({x, y+1, z}))
                        {
                            addFace(yPlusFace, voxelPos, element_count, m_colours[colour_ind], yPlusNormal);
                        }
                        if (!isVoxelThere({x, y, z-1}))
                        {
                            addFace(zMinusFace, voxelPos, element_count, m_colours[colour_ind], zMinusNormal);
                        }
                        if (!isVoxelThere({x, y, z+1}))
                        {
                            addFace(zPlusFace, voxelPos, element_count, m_colours[colour_ind], zPlusNormal);
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
    vao.addVertexBuffer(3, m_mesh.normals);
    vao.addElementBuffer(m_mesh.elements);
    return vao;
}

