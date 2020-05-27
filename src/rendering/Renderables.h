
#pragma once

#include <glm/vec3.hpp>
#include "../VertexArrayObject.hpp"

struct ChunkRenderable final
{
    ChunkPos position;
    VertexArrayObject vao;
};