#pragma once

#include "../pch/pch_std.h"

class VertexArrayObject;

class SceneNode
{
public:
    SceneNode(VertexArrayObject* mesh_vao);

    void             setTransform(const glm::mat4& matrix) { transform = matrix;     }
    const glm::mat4& getTrasforms()             const      { return transform;       }
    glm::mat4        getWorldTransform()        const      { return world_transform; }

    const VertexArrayObject* getVAO() const { return vao; }
    void setVAO(VertexArrayObject* new_vao) { vao = new_vao; }

    void addChild(SceneNode& new_node);

    virtual void update(/* float timestep */);
    virtual void draw();

    std::vector<std::unique_ptr<SceneNode>>::const_iterator getChildIteratorStart() {return children.begin();}
    std::vector<std::unique_ptr<SceneNode>>::const_iterator getChildIteratorEnd() {return children.end();}

protected:
    SceneNode* parent;
    //VAO/mesh
    VertexArrayObject* vao; //VAO is owned by mesh handler

    glm::mat4 world_transform;
    glm::mat4 transform;

    std::vector<std::unique_ptr<SceneNode> > children;

private:
};