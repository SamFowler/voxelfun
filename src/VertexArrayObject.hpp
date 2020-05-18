#pragma once

#include <GL/glew.h>
#include <GL/glu.h>

#include <vector>


class DrawableVAO {
public:
    DrawableVAO(GLuint vao_id, GLsizei num_elements);

    void BindAndDraw(GLenum drawMode = GL_TRIANGLES) const;
    void Bind() const;
    void Draw(GLenum drawMode = GL_TRIANGLES) const;

private:
    const GLuint m_id = 0;
    const GLsizei m_numElements = 0;
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

    void Create();
    void Destroy();
    void Bind();
    void Draw(GLenum drawMode = GL_TRIANGLES);
    void DrawArrays(GLenum drawMode = GL_TRIANGLES);

    DrawableVAO GetDrawable() const;


    void AddVertexBuffer(int num_elements_per_vertex, const std::vector<GLfloat>& vertex_data);
    void AddVertexBuffer(int num_elements_per_vertex, const std::vector<GLuint>& vertex_data);

    void AddElementBuffer(const std::vector<GLuint>& vertex_data);

private:
    void Reset();

    GLuint m_id = 0;
    GLsizei m_numElements = 0;
    std::vector<GLuint> m_bufferObjects;

};