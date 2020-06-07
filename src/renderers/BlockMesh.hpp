#pragma once

//#include <vector>
//#include <GL/glew.h>

#include "../pch/pch_std.h"

#include "../opengl_api/VertexArrayObject.hpp"

class BlockMesh
{

public:

    VertexArrayObject createBuffer();
    VertexArrayObject createBlockBuffer();


    std::vector<GLuint> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLuint> normals;

    std::vector<GLuint> elements;
};