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
    void updateSettings(Input& input);
    void draw(const Camera& camera);
    void destroy();

private:

    bool m_line_mode = false;

    GLint uniform_model;
    GLint uniform_vp;
    GLint uniform_lightpos;
    GLint uniform_normalMat;
    Shader m_shader;

};