/* 
https://github.com/Hopson97/open-builder/blob/master/LICENSE
MIT License

Copyright (c) 2019 Matthew Hopson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/


#pragma once

#include "../pch/pch_std.h"


class DrawableVAO 
{
public:
    DrawableVAO(GLuint vao_id, GLsizei num_elements);
/*     ~DrawableVAO();
 */
    void bindAndDraw(GLenum draw_mode = GL_TRIANGLES) const;
    void bind() const;
    void draw(GLenum draw_mode = GL_TRIANGLES) const;
    void drawWire() const;
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