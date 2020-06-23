#include "Textures.h"

#include "../world/SectorColours.h"

namespace {
    GLuint createTexture()
    {
        GLuint handle;
        glGenTextures(1, &handle);
        glActiveTexture(GL_TEXTURE0);
        return handle;
    }

    void destroyTexture(GLuint* texture)
    {
        glDeleteTextures(1, texture);
        *texture = 0;
    }

} // namespace

Texture2d::Texture2d()
    : m_handle{createTexture()}
{
}

Texture2d::~Texture2d()
{
    destroy();
}

Texture2d::Texture2d(Texture2d&& other)
{
    *this = std::move(other);
}

Texture2d& Texture2d::operator=(Texture2d&& other)
{
    destroy();
    m_has_texture = other.m_has_texture;
    m_handle = other.m_handle;
    other.reset();
    return *this;
}

void Texture2d::create(const SectorColours& sector_colours)
{
    if (!m_handle) {
        m_handle = createTexture();
    }
    bind();

    const std::vector< std::vector< Colour> >& colours = sector_colours.getColoursRef();
    
    uint32_t width = 64; // colour id in Voxel currently takes 6 bits (hence 64). Could change to take in actual width used?
    uint32_t height = 32; // currently using 32 voxel types

    std::vector<uint8_t> texels(width*height*4, 0);

    for (uint32_t v = 0; v < colours.size(); v++)
    {
        for (uint32_t u = 0; u < colours[v].size(); u++ )
        {
            size_t index = v*4*width + u*4;
            texels[index] = colours[v][u].r;
            texels[index+1] = colours[v][u].g;
            texels[index+2] = colours[v][u].b;
            texels[index+3] = colours[v][u].a;
        }
    } 

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                            0, GL_RGBA, GL_UNSIGNED_BYTE, texels.data());
     
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

    m_has_texture = true;
}

void Texture2d::destroy()
{
    destroyTexture(&m_handle);
}

void Texture2d::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

bool Texture2d::textureExists() const
{
    return m_has_texture;
}

void Texture2d::reset()
{
    m_handle = 0;
    m_has_texture = false;
}