
#pragma once

#include "../pch/pch_std.h"

#include "../opengl_api/VertexArrayObject.h"

struct WorldRenderable final
{
    WorldPos position;
    VertexArrayObject vao;
};