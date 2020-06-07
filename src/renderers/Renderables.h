
#pragma once

#include "../pch/pch_std.h"
//#include <glm/vec3.hpp>

#include "../opengl_api/VertexArrayObject.hpp"

struct BlockRenderable final
{
    BlockPos position;
    VertexArrayObject vao;
};