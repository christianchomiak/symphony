#include "GameObject.h"

#include "../Debugging/Debugging.h"

//TO-DO: Figure out a better way to remove elements than by using <algorithm>
#include <algorithm>

namespace Symphony
{
    GameObject::GameObject() : name("New GameObject")
    {
        enabled = true;
        renderObject = nullptr;
    }

    GameObject::~GameObject()
    {
        //TO-DO: Should this be in `Transform` ?
        if (transform.parent != nullptr) transform.parent->RemoveChild(this);

        for (GameObject* go : children)
        {
            if (go)
            {
                go->transform.parent = nullptr;
                delete go;
            }
        }

        delete renderObject;
    }

    void GameObject::Update()
    {
        if (enabled)
        {
            transform.UpdateWorldMatrix();

            for (GameObject* go : children)
            {
                if (go != nullptr && go->enabled) go->Update();
            }
        }
    }

    void GameObject::AddChild(GameObject* child)
    {
        if (child == nullptr) return;

        children.push_back(child);
        child->transform.parent = this;
    }

    void GameObject::RemoveChild(GameObject* child)
    {
        if (child == nullptr) return;

        children.erase(std::remove(children.begin(), children.end(), child), children.end());
        child->transform.parent = nullptr;
    }

    void Symphony::GameObject::SetParent(GameObject* newParent)
    {
        if (transform.parent != nullptr) transform.parent->RemoveChild(this);

        if (newParent != nullptr) newParent->AddChild(this);
        else                      transform.parent = nullptr;
    }

    //TO-DO: There's no need to have this inline, right? RIGHT?
    void Symphony::GameObject::AddRenderObject(RenderObject* rObject)
    {
        if (rObject != nullptr)
        {
            renderObject = rObject;
        }
    }
}