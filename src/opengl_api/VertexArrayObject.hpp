#pragma once

//#include <GL/glew.h>
//#include <GL/glu.h>
//
//#include <vector>

#include "../pch/pch_std.h"


class DrawableVAO 
{
public:
    DrawableVAO(GLuint vao_id, GLsizei num_elements);

    void bindAndDraw(GLenum draw_mode = GL_TRIANGLES) const;
    void bind() const;
    void draw(GLenum draw_mode = GL_TRIANGLES) const;

private:
    const GLuint m_id = 0;
    const GLsizei m_num_elements = 0;
};

class VertexArrayObject 
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    VertexArrayObject(VertexArrayObject&& other);
    VertexArrayObject& operator=(VertexArrayObject&& other);

    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject& operator=(const VertexArrayObject&) = delete;

    void create();
    void destroy();
    void bind() const;
    void draw(GLenum draw_mode = GL_TRIANGLES) const;

    DrawableVAO getDrawable() const;

    void addVertexBuffer(int num_elements_per_vertex, const std::vector<GLfloat>& vertices);
    void addVertexBuffer(int num_elements_per_vertex, const std::vector<GLuint>& vertices);

    void addElementBuffer(const std::vector<GLuint>& vertex_data);

private:
    void reset();

    GLuint m_id = 0;
    GLsizei m_num_elements = 0;
    std::vector<GLuint> m_buffer_objects;

};