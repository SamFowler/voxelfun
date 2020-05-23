#pragma once

#include <vector>
#include "BlockMeshGenerator.hpp"
#include "Mesh.hpp"

using BlockID = unsigned int;

class BlockMeshManager
{
public:
    BlockMeshManager() {
        m_block_meshes.push_back(Mesh());//add empty mesh to represent air
        }
    void updateAllMeshes() {};
    void updateMesh() const {};

    void addMesh(const Mesh& mesh) {m_block_meshes.push_back(mesh);}
    void updateMesh(const Mesh& mesh, const BlockID& block_id) {m_block_meshes[block_id] = mesh;}
    const Mesh getMesh(const BlockID& block_id) const { return m_block_meshes[block_id]; }

private:
    std::vector<unsigned int> m_meshes_to_be_updated;
    std::vector<Mesh> m_block_meshes; //TODO: change to unordered map
};