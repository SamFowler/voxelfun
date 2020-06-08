#include "WireframeMeshGenerator.h"

#include "BlockMesh.h"

namespace WireframeMeshGenerator
{
VertexArrayObject makeBlockVAO(Colour colour)
{
    BlockMesh mesh;
    int index = 0;
    for (int i = 0; i < 24; i++)
    {
        mesh.vertices.push_back(CUBE_LINES_MESH[index++]);
        mesh.vertices.push_back(CUBE_LINES_MESH[index++]);
        mesh.vertices.push_back(CUBE_LINES_MESH[index++]);

        mesh.colours.push_back(colour.r/255.0f);
        mesh.colours.push_back(colour.g/255.0f);
        mesh.colours.push_back(colour.b/255.0f);       
    }

    return mesh.createWireBuffer();
}

}