#pragma once

#include "../pch/pch_std.h"

#include "../opengl_api/VertexArrayObject.h"

class VertexArrayObject;

class BlockMesh
{
public:
    VertexArrayObject createBuffer();
    VertexArrayObject createWireBuffer();

    std::vector<GLuint> vertex_data;
    std::vector<GLuint> elements;
};