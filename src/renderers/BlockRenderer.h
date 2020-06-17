#pragma once

#include "../pch/pch_std.h"
#include "../opengl_api/Shader.h"
#include "../camera/Camera.h"
#include "../world/Block.h"
#include "Renderables.h"
#include "../Input.h"




class SectorColours; //

class BlockRenderer
{
public:
    void init();
    //void getNewBlockUpdates(const std::vector<const Block*> updated_blocks);

    std::vector<std::pair<const BlockPos, Block&> >& getRefToRemeshList();


    void addSelectorVAO(WorldPos renderable_pos);
    void updateSelectorPosition(const WorldPos& selector_pos);

    void updateSettings(Input& input);

    void updateVAOs(const SectorColours& sector_colours /* this is temp here before this renderer gets moved */);
    void draw(const Camera& camera);
    void destroy();

private:

    bool m_line_mode = false;

    std::vector<std::pair<const BlockPos, Block&> > m_blocks_to_remesh;
    
    std::unordered_map<BlockPos, unsigned int, PositionHash> m_world_renderable_indexes;
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