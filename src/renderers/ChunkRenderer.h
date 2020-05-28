#pragma once

#include "../opengl_api/Shader.hpp"
#include "../opengl_api/VertexArrayObject.hpp"
#include "../camera/PerspectiveCamera.hpp"
#include "../world/Chunk.h"
#include <vector>

class ChunkRenderer
{
public:
    void init();
    void getNewChunkUpdates(const std::vector<const Chunk*> updated_chunks);
    void updateVAOs();
    void draw(const PerspectiveCamera& camera);
    void destroy();
private:

    std::vector<const Chunk*> m_updated_chunk_list;
    std::vector<VertexArrayObject> m_chunk_vaos;
    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;
    Shader m_shader;

};