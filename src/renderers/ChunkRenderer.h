#pragma once

#include "../opengl_api/Shader.hpp"
#include "../opengl_api/VertexArrayObject.hpp"
#include "../camera/PerspectiveCamera.hpp"

#include "../world/Chunk.h"
//#include <vector>

#include "../pch/pch_std.h"

#include "Renderables.h"

class ChunkRenderer
{
public:
    void init(const unsigned int& chunk_size);
    void getNewChunkUpdates(const std::vector<const Chunk*> updated_chunks);
    void updateVAOs();
    void draw(const PerspectiveCamera& camera);
    void destroy();
private:

    float m_chunk_offset;
    unsigned int m_chunk_size;

    std::vector<const Chunk*> m_updated_chunk_list;
    std::vector<VertexArrayObject> m_chunk_vaos;
    std::vector<ChunkRenderable> m_chunk_renderables;
    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;
    Shader m_shader;

};