#pragma once

#include <vector>
#include <GL/glew.h>

#include "VertexArrayObject.hpp"

class Mesh
{

public:

    VertexArrayObject createBuffer();


    std::vector<GLuint> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLfloat> normals;

    std::vector<GLuint> elements;
};