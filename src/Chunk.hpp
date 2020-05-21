#pragma once

#include <vector>
#include "VertexArrayObject.hpp"

#include <glm/vec3.hpp>

struct pos3d
{
    int x = 0;
    int y = 0;
    int z = 0;
};

struct colour
{
    float r = 1.0f, g = 0.0f, b = 1.0f;
};



enum voxel_type 
{
    AIR = 0,
    BLOCK,
    COUNT
};

class ChunkMesh
{
public:
    std::vector<GLuint> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLuint> elements;
private:
    
     
};

struct ChunkRenderable final {
    glm::vec3 position;
    VertexArrayObject vao;
};

class Chunk
{
public:
    Chunk(const glm::vec3 position, const int side_size = 16);
    Chunk(const glm::vec3 position, const std::vector<glm::vec3> colours, const int side_size = 16);

    int getVolume() {return m_volume;}
    int getSideSize() {return m_side;}
    int getVoxelVectorLength() {return m_voxels.size();}
    glm::vec3 getPosition() {return m_position;}

    void changeVoxel(const glm::ivec3& position, const unsigned int type);
    void removeVoxel(const glm::ivec3& position);


    unsigned int getVoxelType(const glm::ivec3& position);
    bool isVoxelThere(const glm::ivec3& position);
    bool isVoxelThere_Safe(const glm::ivec3& position);

    //bool isChunkEdge(const glm::ivec3& position, const chunk_edge& edge);
    bool isOutsideChunk(const glm::ivec3& position);
    bool isChunkEdge(const glm::ivec3& position);

     VertexArrayObject getInitialVao();

    int getVoxelIndex(const glm::ivec3& voxel_position);
    void addFace(const std::vector<GLuint>& faceVerts, const glm::ivec3& voxelPos, int& element_count, const glm::vec3& col);
    void makeChunkMesh();
    void makeEfficientChunkMesh();
    void makeColouredEfficientChunkMesh();
    void createVao();

    VertexArrayObject createAndGetVao();

    void bindAndDraw();

private:
    glm::vec3 m_position;

    ChunkMesh m_mesh;

    int m_side;
    int m_side_sq;

    int m_volume;

    std::vector<glm::vec3> m_colours;
    std::vector<unsigned int> m_voxels;
};