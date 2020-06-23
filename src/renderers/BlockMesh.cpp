#include "BlockMesh.h"

VertexArrayObject BlockMesh::createWireBuffer()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    //vao.addVertexBuffer(3, vertices);
    //vao.addVertexBuffer(3, colours);
    return vao;
}

VertexArrayObject BlockMesh::createBuffer()
{
    VertexArrayObject vao;
    vao.create();
    vao.bind();
    vao.addVertexBuffer(1, vertex_data);
    vao.addElementBuffer(elements);
    return vao;
}