#include "BlockMesh.h"

VertexArrayObject BlockMesh::createWireBuffer()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(3, vertices);
    vao.addVertexBuffer(3, colours);
    return vao;
}



VertexArrayObject BlockMesh::createBuffer()
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