#include "Mesh.hpp"

VertexArrayObject Mesh::createBuffer()
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



VertexArrayObject Mesh::createChunkBuffer()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, vertices);
    vao.addVertexBuffer(4, colours);
    //vao.addVertexBuffer(3, normals);
    vao.addElementBuffer(elements);
    return vao;
}