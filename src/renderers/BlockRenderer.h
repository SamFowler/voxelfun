#pragma once

#include "../pch/pch_std.h"
#include "../opengl_api/Shader.h"
#include "../camera/Camera.h"
#include "../world/Block.h"
#include "Renderables.h"

class BlockRenderer
{
public:
    void init(const unsigned int& block_size);
    //void getNewBlockUpdates(const std::vector<const Block*> updated_blocks);

    std::vector<std::pair<const BlockPos, const Block*> >& getRefToRemeshList();
    void updateVAOs();
    void draw(const Camera& camera);
    void destroy();
private:

    float m_block_offset;
    unsigned int m_block_size;

    std::vector<std::pair<const BlockPos, const Block*> > m_blocks_to_remesh;
    std::vector<BlockRenderable> m_block_renderables;
    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;
    Shader m_shader;

};