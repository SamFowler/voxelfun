#include "SceneNode.h"

#include "VertexArrayObject.h"

SceneNode::SceneNode(VertexArrayObject* mesh_vao)
 : parent(nullptr), vao(mesh_vao)
{}


void SceneNode::addChild(SceneNode& new_node)
{
    children.push_back(std::make_unique<SceneNode>(new_node));
    --children.end()->get()->parent = this;
}

void SceneNode::draw()
{
    if (vao) 
        vao->getDrawable().draw();
}

void SceneNode::update(/* float timestep */)
{
    if (parent)
        world_transform = parent->world_transform * transform;
    else //is root node
        world_transform = transform;

    for (auto it = children.begin(); it != children.end(); ++it)
        (*it)->update(/* timestep */);
}

    
