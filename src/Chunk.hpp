#pragma once

#include <vector>
#include "VertexArrayObject.hpp"

struct pos3d
{
    int x = 0;
    int y = 0;
    int z = 0;
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
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLuint> elements;
private:
    
     
};

class Chunk
{
public:
    Chunk(const pos3d position, const int& side_size = 16);

    int getVolume() {return m_volume;}
    int getSizeSize() {return m_side;}
    int getVoxelVectorLength() {return m_voxels.size();}
    pos3d getPosition() {return m_position;}

    
    int getVoxelIndex(const pos3d& voxel_position);
    void makeChunkMesh();
    VertexArrayObject createVao();

private:
    pos3d m_position;

    ChunkMesh m_mesh;
    //VertexArrayObject m_vao;

    int m_side;
    int m_side_sq;

    int m_volume;

    std::vector<voxel_type> m_voxels;
};