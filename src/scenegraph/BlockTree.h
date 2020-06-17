#pragma once

#include "../pch/pch_std.h"

#include "Node.h"
#include "../world/Coordinates.h"

class BlockNode;

class BlockTree : public Node
{
private:

    std::array<std::unique_ptr<Node>, 8> m_children;

public:
    BlockTree(const glm::uvec3& origin, const glm::uvec3& half_size) { m_origin = origin; m_half_size = half_size; };

    void draw(const Uniforms& uniforms) ;

    uint8_t getOctantContainingPos(const BlockPos& pos) const;
    void addBlock(const BlockPos& pos, BlockNode& block_node);
    void deleteBlock(const BlockPos& pos);

private:
    bool isEmpty();

};