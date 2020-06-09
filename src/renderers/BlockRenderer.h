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

    std::vector<std::pair<const BlockPos, Block&> >& getRefToRemeshList();


    void addSelectorVAO(WorldPos renderable_pos);
    void updateSelectorPosition(const WorldPos& selector_pos);

    void updateVAOs();
    void draw(const Camera& camera);
    void destroy();

private:

    float m_block_offset;
    unsigned int m_block_size;

    std::vector<std::pair<const BlockPos, Block&> > m_blocks_to_remesh;
    
    std::vector<WorldRenderable> m_world_renderables;
    std::unique_ptr<WorldRenderable> mp_wire_selector_renderable;

    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;
    Shader m_shader;

    Shader m_wire_shader;
    GLint wire_uniform_model;
    GLint wire_uniform_vp;

};