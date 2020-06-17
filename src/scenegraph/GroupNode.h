#pragma once

#include "../pch/pch_std.h"



class GroupNode
{
private:
    std::list<std::unique_ptr<GroupNode>> m_children;

protected:
    GroupNode* m_parent;

public:
    virtual void draw()
    {
        for (std::list<std::unique_ptr<GroupNode>>::iterator it = m_children.begin(); it != m_children.end(); ++it)
        {
            (*it)->draw();
        }
    }

    void addChild(GroupNode& new_node)
    {
        m_children.emplace_back(std::make_unique<GroupNode>(std::move(new_node)));
        --m_children.end()->get()->m_parent = this;
    }
};