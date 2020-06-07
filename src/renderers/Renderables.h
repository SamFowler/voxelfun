
#pragma once

#include "../pch/pch_std.h"

#include "../opengl_api/VertexArrayObject.h"

struct BlockRenderable final
{
    BlockPos position;
    VertexArrayObject vao;
};