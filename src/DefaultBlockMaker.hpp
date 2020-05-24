#include "Block.hpp"

enum DefaultBlockType 
{
    GRASS_ONE = 0,
    GRASS_TWO,
    DIRT_ONE,
    TREE_ONE,
    PLACEHOLDER
};


namespace DefaultBlockMaker {
    Block makeBlock(const int& block_size, const DefaultBlockType& block_type = PLACEHOLDER);
    Block makeGrassOne(const int& block_size);
    Block makeGrassTwo(const int& block_size);
    Block makeDirtOne(const int& block_size);
    Block makePlaceholder(const int& block_size);

}