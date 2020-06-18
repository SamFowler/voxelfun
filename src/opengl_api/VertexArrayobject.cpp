#include "VertexArrayObject.h"

/* 
    ---------------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------------
    Drawable VAO functions
    ---------------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------------
*/ 
DrawableVAO::DrawableVAO(GLuint vao_id, GLsizei num_elements)
: m_id(vao_id), m_num_elements(num_elements)
{
    
}

/* ~DrawableVAO::DrawableVAO()
{
    glDeleteVertexArrays(1, &m_id);
    //glDeleteBuffers(m_buffer_objects.size(), m_buffer_objects.data());
} */

void DrawableVAO::bindAndDraw(GLenum draw_mode) const
{
    bind();
    draw(draw_mode);
}

void DrawableVAO::bind() const
{
    glBindVertexArray(m_id);
}

void DrawableVAO::draw(GLenum drawMode) const
{
    glDrawElements(drawMode, m_num_elements, GL_UNSIGNED_INT, nullptr);
}

void DrawableVAO::drawWire() const
{
    glDrawArrays(GL_LINES, 0, 24);
}



/* 
    ---------------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------------
    VertexArrayObject functions
    ---------------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------------
*/ 

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
    destroy();
} 

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) 
{
    *this = std::move(other);
}

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& other)
{
    destroy();
    m_buffer_objects = std::move(other.m_buffer_objects);
    m_id = other.m_id;
    m_num_elements = other.m_num_elements;
    other.reset();
    return *this;
}    

void VertexArrayObject::create()
{
    if (!m_id)
    {
        glGenVertexArrays(1, &m_id);
    }
}   

void VertexArrayObject::destroy()
{
    //glDeleteVertexArrays(1, &m_id);
    //glDeleteBuffers(m_buffer_objects.size(), m_buffer_objects.data());
    reset();
}

void VertexArrayObject::bind() const
{
    glBindVertexArray(m_id);
}

DrawableVAO VertexArrayObject::getDrawable() const
{
    return {m_id, m_num_elements};
}

void VertexArrayObject::draw(GLenum draw_mode) const
{
    glDrawElements(draw_mode, m_num_elements, GL_UNSIGNED_INT, nullptr);

}

void VertexArrayObject::addVertexBuffer(int num_elements_per_vertex, const std::vector<GLfloat>& vertices)
{
    
    bind(); //set this VAO as "active"

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id); //generate VBO and get identifier
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //set VBO as "active"

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW); //put vertex data in active VBO

    //std::cout << "Adding float vertex VBO with id " << vbo_id << ", size " << vertices.size() << std::endl;

    //tell the buffer what our VBO data is
    glVertexAttribPointer(
        m_buffer_objects.size(), //id of this VBO within the VAO. Set as m_buffer_objects.size() as that represents the current number of VBOs within VAO
        num_elements_per_vertex, // i.e. x,y = 2, x,y,z = 3, r,g,b,a = 4
        GL_FLOAT, //type of the element within the vertex data (float/int/etc)
        GL_FALSE, //whether to get openGL to normalise fixed point data values (e.g. 0 to 255) to between 0.0 and 1.0 when accessed by glsl
        0,  // byte offset between vertex attributes. Set to 0 as assuming each input data holds only one attribute (i.e vertex_data holds vertex positons OR vertex colours OR vertex normals, etc)
        nullptr //offset of first element. not used as assuming one attribute as above
    );

    glEnableVertexAttribArray(m_buffer_objects.size()); //set VBO to used for rendering calls

    m_buffer_objects.push_back(vbo_id); // add VBO id to list of VBOs within VAO

}

void VertexArrayObject::addVertexBuffer(int num_elements_per_vertex, const std::vector<GLuint>& vertices)
{
    
    bind(); //set this VAO as "active"
    
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id); //generate VBO and get identifier
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id); //set VBO as "active"

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLuint), vertices.data(), GL_STATIC_DRAW); //put vertex data in active VBO

    //std::cout << "Adding int vertex VBO with id " << vbo_id << ", size " << vertices.size() << std::endl;

    //tell the buffer what our VBO data is
    glVertexAttribIPointer(
        m_buffer_objects.size(), //id of this VBO within the VAO. Set as m_buffer_objects.size() as that represents the current number of VBOs within VAO
        num_elements_per_vertex, // i.e. x,y = 2, x,y,z = 3, r,g,b,a = 4
        GL_UNSIGNED_INT, //type of the element within the vertex data (float/int/etc)
        0,  // byte offset between vertex attributes. Set to 0 as assuming each input data holds only one attribute (i.e vertex_data holds vertex positons OR vertex colours OR vertex normals, etc)
        nullptr //offset of first element. not used as assuming one attribute as above
    );

    glEnableVertexAttribArray(m_buffer_objects.size()); //set VBO to used for rendering calls

    m_buffer_objects.push_back(vbo_id); // add VBO id to list of VBOs within VAO

}

void VertexArrayObject::addElementBuffer(const std::vector<GLuint>& elements)
{
    bind();
    GLuint eb_id;
    glGenBuffers(1, &eb_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);

    std::cout << "Adding element VBO with id " << eb_id << ", size " << elements.size() << std::endl;

    m_buffer_objects.push_back(eb_id);
    m_num_elements = elements.size();
}

void VertexArrayObject::reset() 
{
    m_buffer_objects.clear();
    m_id = 0;
    m_num_elements = 0;
}

