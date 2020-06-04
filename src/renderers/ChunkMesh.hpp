#pragma once

//#include <vector>
//#include <GL/glew.h>

#include "../pch/pch_std.h"

#include "../opengl_api/VertexArrayObject.hpp"

class ChunkMesh
{

public:

    VertexArrayObject createBuffer();
    VertexArrayObject createChunkBuffer();


    std::vector<GLuint> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLuint> normals;

    std::vector<GLuint> elements;
};