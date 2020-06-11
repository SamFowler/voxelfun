#pragma

#include "../pch/pch_std.h"

#include "SceneNode.h"

#include "../world/Coordinates.h"

/* 
    SECTOR NODE
 */
class SectorNode : public SceneNode
{
public:
    SectorNode(void);
    virtual void update();
protected:
    SectorPos sector_pos;
};


/* 
    BLOCK NODE
 */
class BlockNode : public SceneNode
{
public:
    BlockNode(void);
    virtual void update();
protected:
    BlockPos block_pos;
};