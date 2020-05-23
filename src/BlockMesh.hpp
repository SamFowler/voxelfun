#pragma once

#include <vector>
#include <GL/glew.h>



class BlockMesh
{

public:

    std::vector<GLuint> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLfloat> normals;

    std::vector<GLuint> elements;
};