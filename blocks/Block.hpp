#pragma once

#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

using Colour = glm::vec4;
using VoxelID = unsigned int;
/*struct Voxel
{
    unsigned int colour_index;
    //unsigned int voxel_type;
    //unsigned int light_level;
};*/

class Block
{
public:
    //Block(const unsigned int& size, const int& block_id, const std::vector<VoxelID>& voxels, const std::vector<Colour> colours)
    //: m_size(size), m_block_id(block_id), m_voxels(voxels), m_colours(colours)
    /*Block(const unsigned int& size, std::vector<VoxelID>& voxels, const std::vector<Colour>& colours)
    : m_size(size), m_voxels(voxels), m_colours(colours)
    {
    };*/
    Block(unsigned int size, std::vector<VoxelID> voxels, std::vector<Colour> colours)
    : m_size(std::move(size)), m_voxels(std::move(voxels)), m_colours(std::move(colours))
    {
        //makeNeighbours();
    };

    unsigned int getSize() const { return m_size; }

    VoxelID getVoxel(const unsigned int& voxel_index) const { return m_voxels[voxel_index]; };
    VoxelID getVoxel(const glm::vec3& pos) const {return m_voxels[pos.x + pos.z*m_size + pos.y*m_size*m_size]; };
    //TODO: need to add bounds checking. make a safe function and non-safe function
    void setVoxel(const unsigned int& voxel_index, const VoxelID& voxel_id) { m_voxels[voxel_index] = voxel_id; };

    Colour getColour(const VoxelID& voxel_id) const { return m_colours[voxel_id];};

    //changes all voxels with voxel_id to replacement_id
    void changeVoxelID(const VoxelID& voxel_id, const VoxelID& replacement_id = 0);

    //calls changeVoxelID to set voxels with voxel_id to empty, then "removes" the colour
    //NOTE: doesn't actually remove colour from m_colour yet, changes it to negative floats
    //TODO: change m_colours to unordered_map (aka hash table) so it can be properly removed?
    void removeColour(const VoxelID& colour_id);

    VoxelID addColour(const Colour& colour);

    void makeNeighbours();
    char getNeighbours(const unsigned int& voxel_index) { return m_neighbours[voxel_index];};
    char getNeighbours(const glm::vec3& pos) const {return m_neighbours[pos.x + pos.z*m_size + pos.y*m_size*m_size]; };


    //unsigned int getBlockId() const { return m_block_id; }
    //void setBlockId(const unsigned int& block_id) { m_block_id = block_id; }


private:
    unsigned int m_size;
    //unsigned int m_block_id = 0;
    //unsigned int light_level = 0;

    std::vector<VoxelID> m_voxels;
    std::vector<Colour> m_colours;
    std::vector<char> m_neighbours; 

};