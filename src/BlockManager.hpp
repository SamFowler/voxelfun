#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include "Block.hpp"

#include "BlockMeshGenerator.hpp"
//#include "VertexArrayObject.hpp"

using BlockID = unsigned int;

class BlockManager
{
public:
    //BlockManager(int& empty_block_size);
    BlockManager();
    BlockManager(const unsigned int& default_block_size, const int& numBlocks = 15);

    // gets the number of blocks currently stored within this manager
    int getNumBlocks() const { return m_blocks.size(); }

    // add a new block to the manager
    BlockID addBlock(const Block& block);
    BlockID addBlock(const unsigned int& size, const std::vector<VoxelID>& voxels, const std::vector<Colour> colours);

    // remove block from the manager
    bool removeBlock(const BlockID& block_id);

    // get reference to block which is within the manager
    const Block* getBlock(const BlockID& block_id) const;

    //within the Block at block_id: change Voxels at voxel_indexes to voxel_id
    void changeVoxelsInBlock(const BlockID& block_id, const unsigned int& voxel_index, const VoxelID& voxel_id);
    void changeVoxelsInBlock(const BlockID& block_id, const std::vector<unsigned int>& voxel_indexes, const VoxelID& voxel_id);

    // calls changeVoxelsInBlock to set voxel_indexes to empty
    void removeVoxelsFromBlock(const BlockID& block_id, const unsigned int& voxel_index);
    void removeVoxelsFromBlock(const BlockID& block_id, const std::vector<unsigned int>& voxel_indexes);

    // changes voxels with voxel_id to replacement_id
    void changeColourInBlock(const BlockID& block_id, const VoxelID& voxel_id, const VoxelID& replacement_id);

    // add a new colour to the Block at block_id. Returns id of this new colour
    VoxelID addColourToBlock(const BlockID& block_id, const Colour& colour);
    // remove colour from block, sets voxels of that colour to empty
    void removeColourFromBlock(const BlockID& block_id, const VoxelID& voxel_id);


    //void update(const MeshMethod& method = CULL_MESH_FAST);

    DrawableVAO getDrawableVAO(const BlockID& block_id) { return m_block_vaos[block_id].getDrawable(); }

    void updateDrawables(std::unordered_map<BlockID, VertexArrayObject>& block_drawables, const MeshMethod& method = CULL_MESH_FAST);

private:
    //std::vector<int> m_block_ids;
    std::queue<BlockID> m_free_block_ids = {};
    //std::map<BlockID, Block> m_blocks;
    std::vector<std::unique_ptr<Block>> m_blocks;
    //std::vector<Block> m_blocks;

    std::unordered_map<BlockID, VertexArrayObject> m_block_vaos;
    std::vector<BlockID> m_updated_blocks = {};

};