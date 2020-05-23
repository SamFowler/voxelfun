#pragma once

#include <vector>
#include "BlockMeshGenerator.hpp"



class BlockMeshManager
{
public:

    void updateAllMeshes();
    void updateMesh();



private:
    std::vector<unsigned int> m_meshes_to_be_updated;
    std::vector<Mesh> m_block_meshes;
};