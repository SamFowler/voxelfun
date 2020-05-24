#include "World.hpp"

void World::init()
{

}

void World::update(const Input& input)
{



}

std::vector<BlockRenderList*> World::getWorldRenderList()
{
    std::vector<BlockRenderList*> render_list;
    for (auto& it : m_chunk_ptrs)
    {
        render_list.push_back(it->getBlockRenderListPtr());
        //render_list.push_back()
    }
    return render_list;
    /*
    for (auto it : m_chunks)
    {
        render_list.push_back(it.getBlockRenderList());
    }
    return render_list;
    */
}


