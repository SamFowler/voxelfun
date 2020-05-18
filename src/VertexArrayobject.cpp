#include "VertexArrayObject.hpp"
#include <iostream>



/* 
    --------------------------------------------------------------------------
    Drawable VAO functions
    --------------------------------------------------------------------------
*/ 
DrawableVAO::DrawableVAO(GLuint vao_id, GLsizei num_elements)
: m_id(vao_id), m_numElements(num_elements)
{
}

void DrawableVAO::BindAndDraw(GLenum drawMode) const
{
    Bind();
    Draw(drawMode);
}

void DrawableVAO::Bind() const
{
    glBindVertexArray(m_id);
}

void DrawableVAO::Draw(GLenum drawMode) const
{
    glDrawElements(drawMode, m_numElements, GL_UNSIGNED_INT, nullptr);
}



/* 
    --------------------------------------------------------------------------
    VertexArrayObject functions
    --------------------------------------------------------------------------
*/ 

VertexArrayObject::VertexArrayObject()
{

}
VertexArrayObject::~VertexArrayObject()
{
    Destroy();
} 

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) 
{
    *this = std::move(other);
}

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& other)
{
    Destroy();
    m_bufferObjects = std::move(other.m_bufferObjects);
    m_id = other.m_id;
    m_numElements = other.m_numElements;
    other.Reset();
    return *this;
}

    

void VertexArrayObject::Create()
{
    if (!m_id)
    {
        glGenVertexArrays(1, &m_id);
    }
}   

void VertexArrayObject::Destroy()
{
    glDeleteVertexArrays(1, &m_id);
    glDeleteBuffers(m_bufferObjects.size(), m_bufferObjects.data());
    Reset();
}

void VertexArrayObject::Bind()
{
    glBindVertexArray(m_id);
}

DrawableVAO VertexArrayObject::GetDrawable() const
{
    return {m_id, m_numElements};
}

void VertexArrayObject::Draw(GLenum drawMode)
{
    glDrawElements(drawMode, m_numElements, GL_UNSIGNED_INT, nullptr);

}

void VertexArrayObject::DrawArrays(GLenum drawMode)
{
    glDrawArrays(drawMode, 0, 4);

}

void VertexArrayObject::AddVertexBuffer(int num_elements_per_vertex, const std::vector<GLfloat>& vertices)
{
    
    Bind(); //set this VAO as "active"

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id); //generate VBO and get identifier
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //set VBO as "active"

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW); //put vertex data in active VBO

    std::cout << "Adding float vertex VBO with id " << vbo_id << ", size " << vertices.size() << std::endl;

    //tell the buffer what our VBO data is
    glVertexAttribPointer(
        m_bufferObjects.size(), //id of this VBO within the VAO. Set as m_bufferObjects.size() as that represents the current number of VBOs within VAO
        num_elements_per_vertex, // i.e. x,y = 2, x,y,z = 3, r,g,b,a = 4
        GL_FLOAT, //type of the element within the vertex data (float/int/etc)
        GL_FALSE, //whether to get openGL to normalise fixed point data values (e.g. 0 to 255) to between 0.0 and 1.0 when accessed by glsl
        0,  // byte offset between vertex attributes. Set to 0 as assuming each input data holds only one attribute (i.e vertex_data holds vertex positons OR vertex colours OR vertex normals, etc)
        nullptr //offset of first element. not used as assuming one attribute as above
    );

    glEnableVertexAttribArray(m_bufferObjects.size()); //set VBO to used for rendering calls

    m_bufferObjects.push_back(vbo_id); // add VBO id to list of VBOs within VAO

}

void VertexArrayObject::AddVertexBuffer(int num_elements_per_vertex, const std::vector<GLuint>& vertices)
{
    
    Bind(); //set this VAO as "active"

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id); //generate VBO and get identifier
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //set VBO as "active"

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLuint), vertices.data(), GL_STATIC_DRAW); //put vertex data in active VBO

    std::cout << "Adding int vertex VBO with id " << vbo_id << ", size " << vertices.size() << std::endl;

    //tell the buffer what our VBO data is
    glVertexAttribIPointer(
        m_bufferObjects.size(), //id of this VBO within the VAO. Set as m_bufferObjects.size() as that represents the current number of VBOs within VAO
        num_elements_per_vertex, // i.e. x,y = 2, x,y,z = 3, r,g,b,a = 4
        GL_UNSIGNED_INT, //type of the element within the vertex data (float/int/etc)
        0,  // byte offset between vertex attributes. Set to 0 as assuming each input data holds only one attribute (i.e vertex_data holds vertex positons OR vertex colours OR vertex normals, etc)
        nullptr //offset of first element. not used as assuming one attribute as above
    );

    glEnableVertexAttribArray(m_bufferObjects.size()); //set VBO to used for rendering calls

    m_bufferObjects.push_back(vbo_id); // add VBO id to list of VBOs within VAO

}

void VertexArrayObject::AddElementBuffer(const std::vector<GLuint>& elements)
{
    Bind();
    GLuint eb_id;
    glGenBuffers(1, &eb_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);

    std::cout << "Adding element VBO with id " << eb_id << ", size " << elements.size() << std::endl;

    m_bufferObjects.push_back(eb_id);
    m_numElements = elements.size();
}

void VertexArrayObject::Reset() 
{
    m_bufferObjects.clear();
    m_id = 0;
    m_numElements = 0;
}

