#pragma once

//#include <unordered_map>
//#include <queue>
//#include <vector>
//#include <utility>

#include "../pch/pch_std.h"

#include "Block.h"

#include "../Input.hpp" // TODO: unsure if this should go here or not

#include "DefaultBlockMaker.h"

class BlockManager
{
public:
    friend class Block;
    //friend class BlockMeshGenerator;

    // Constructors
    BlockManager(const size_t& block_size = 2) : m_block_size(block_size), 
                                             m_block_size_sq(block_size*block_size),
                                             m_block_volume(block_size*block_size*block_size)
                                             {};
    //BlockManager(const Block& block);
    //BlockManager(const std::vector<Block>& blocks);

    // Processors
    bool init();
    void update(const Input& input);
    void destroy();

    // Getters
    int getNumBlocks() const;
    
    void addBlock(const BlockPos& position, const BlockMakeType&);
    void addBlock(const BlockPos& position, const std::vector<Voxel>& voxels, const std::vector<Colour>& colours);
    //void addBlock    (const Block&              block          );
    //void addBlocks   (const std::vector<Block>& blocks         );
    void replaceBlock(const Block&              block          );
    void addBlockToUpdateList(const BlockPos& block_pos);

    void clearUpdatedBlockList();
    std::vector<const Block*> getUpdatedBlockList() const;
    
    const Block* getBlockPtr(const BlockPos& block_pos) const; 

    Voxel              getVoxel (const VoxelWorldPos&              voxel_world_pos       ) const;
    std::vector<Voxel> getVoxels(const std::vector<VoxelWorldPos>& voxel_world_positions ) const;

    // Public setters (take in voxel world coordinates and call private functions with block/voxel positions)
    void setVoxels      (const std::vector<VoxelWorldPos>& voxel_world_positions, const Voxel& new_voxel);
    void setVoxelsColour(const std::vector<VoxelWorldPos>& voxel_world_positions, const Colour& new_colour);
    void setVoxelsType  (const std::vector<VoxelWorldPos>& voxel_world_positions, const VoxelType& new_type);

private:
    // Helpers
    bool blockExists (const BlockPos&           block_position ) const;
    bool removeBlock (const BlockPos&           block_position );

    BlockAndVoxelPos getBlockVoxelPosFromVoxelWorldPos(const VoxelWorldPos& voxel_world_pos) const;

    //void addColourToBlock (...) //TODO: unsure about this being here at the moment
    //removeColourFromChukn (...) //TODO: unsure about this being here at the moment

    // Private getters
    //const Block&              getBlock  (const BlockPos&                block_position  ) const;
    //const std::vector<Block>& getBlocks (const std::vector<BlockPos>&   block_positions ) const;

    Voxel              getVoxel  (const BlockAndVoxelPos&     block_voxel_pos      ) const;
    std::vector<Voxel> getVoxels (const BlockAndManyVoxelPos& block_voxel_positions) const;

private:

    // Private setters
    void setVoxelsInBlock      (const BlockPos& block_position, const std::vector<glm::ivec3>& block_voxel_positions, const Voxel& new_voxel);
    void setVoxelColoursInBlock(const BlockPos& block_position, const std::vector<glm::ivec3>& block_voxel_positions, const Colour& new_colour);
    void setVoxelTypesInBlock  (const BlockPos& block_position, const std::vector<glm::ivec3>& block_voxel_positions, const VoxelType& new_type);

    // Data
    std::unordered_map<BlockPos, Block, BlockPositionHash> m_blocks;
    int m_num_blocks;

    //std::queue<> m_updated_block_list;
    std::vector<const Block*> m_updated_block_list;

    unsigned int m_block_size;
    unsigned int m_block_size_sq;
    unsigned int m_block_volume;

};