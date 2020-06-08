#pragma once

#include "../pch/pch_std.h"

#include "../opengl_api/VertexArrayObject.h"
#include "../world/Colour.h"

namespace WireframeMeshGenerator
{
    const std::array<GLuint, 72> CUBE_LINES_MESH = {
                                                    0, 0, 0, /*--->*/  0, 0, 1, 
                                                    0, 0, 1, /*--->*/  0, 1, 1,
                                                    0, 1, 0, /*--->*/  0, 1, 1,
                                                    0, 0, 0, /*--->*/  0, 1, 0,

                                                    1, 0, 0, /*--->*/  1, 1, 0,
                                                    1, 1, 0, /*--->*/  1, 1, 1, 
                                                    1, 1, 1, /*--->*/  1, 0, 1, 
                                                    1, 0, 1, /*--->*/  1, 0, 0,

                                                    0, 0, 1, /*--->*/  1, 0, 1,
                                                    0, 1, 1, /*--->*/  1, 1, 1,
                                                    0, 1, 0, /*--->*/  1, 1, 0,
                                                    0, 0, 0, /*--->*/  1, 0, 0, 
                                                    };



    VertexArrayObject makeBlockVAO(Colour colour);

}