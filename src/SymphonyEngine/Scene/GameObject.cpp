#include "GameObject.h"

//TO-DO: Figure out a better way to remove elements than by using <algorithm>
#include <algorithm>

#include <Debugging/Debugging.h>

namespace Symphony
{
    GameObject::GameObject()
        : GameObject("New GameObject")
    {
    }

    GameObject::GameObject(const char* objName)
        : name(objName != nullptr ? objName : "NewGameObject"),
          renderObject(nullptr),
          parent(nullptr),
          enabled(true)
    {
        transform.SetOwner(this);
    }

    GameObject::~GameObject()
    {
        //TODO: Destruction of GameObjects should be handled with care
        //      If the object is destroyed by its parent, then there's no need to use parent->RemoveChild(this);
        //      However, if it's being deleted from another place, the function should be called to notify the parent.

        /*if (parent != nullptr)
        {
            parent->RemoveChild(this);
        }*/
        
        for (GameObject* go : children)
        {
            AssertF(go, "Found a null child in GameObject [%s]", name.GetCString());

            if (go)
            {
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
                AssertF(go, "Found a null child in GameObject [%s]", name.GetCString());

                if (go != nullptr && go->enabled)
                {
                    go->Update();
                }
            }
        }
    }
    
    void GameObject::AddChild(GameObject* child)
    {
        AssertF(child, "Trying to set a null child to GameObject [%s]", name.GetCString());

        //TODO: Search if child is already a child of this object

        for (GameObject* go : children)
        {
            if (go == child)
            {
                LogWarningF("Warning: Trying to re-add the same child [%s] to parent [%s]",
                            child->name.GetCString(), name.GetCString());
                return;
            }
        }

        if (child != nullptr)
        {
            children.push_back(child);

            child->RemoveFromCurrentParent();
            child->parent = this;
            child->transform.UpdateCachedParent();
        }
    }

    void GameObject::RemoveChild(GameObject* child)
    {
        AssertF(child, "Trying to remove a null child from GameObject [%s]", name.GetCString());

        if (child != nullptr)
        {
            children.erase(std::remove(children.begin(), children.end(), child), children.end());
            
            //TODO: Check if child was part of this object, before changing any values from it
            child->parent = nullptr;
            child->transform.UpdateCachedParent();

            //TO-DO: Is this safe when calling RemoveChild in a context other than the child's destructor?
        }
    }

    void GameObject::RemoveFromCurrentParent()
    {
        //Unparent this object from its previous parent
        if (parent != nullptr)
        {
            parent->RemoveChild(this);
        }

        parent = nullptr;

        transform.UpdateCachedParent();
    }

    void GameObject::SetParent(GameObject* newParent)
    {
        //We only want to proceed if we're changing to a *new* parent
        if (newParent == parent)
        {
            return;
        }

        RemoveFromCurrentParent();
        
        if (newParent != nullptr)
        {
            newParent->AddChild(this);
        }
        else
        {
            newParent = nullptr;
        }

        transform.UpdateCachedParent();
    }

    //TO-DO: There's no need to have this inline, right? RIGHT?
    void GameObject::AddRenderObject(RenderObject* rObject)
    {
        if (rObject != nullptr)
        {
            renderObject = rObject;
        }
    }
}