#include "ChunkMesh.hpp"

VertexArrayObject ChunkMesh::createBuffer()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, vertices);
    vao.addVertexBuffer(3, colours);
    vao.addVertexBuffer(3, normals);
    vao.addElementBuffer(elements);
    return vao;
}



VertexArrayObject ChunkMesh::createChunkBuffer()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, vertices);
    vao.addVertexBuffer(4, colours);
    vao.addVertexBuffer(1, normals);
    vao.addElementBuffer(elements);
    return vao;
}