#pragma once

#include <string>
#include <vector>

#include <Rendering/RenderObject.h>
#include <Utilities/HashString.h>

#include "Transform.h"

namespace Symphony
{
    class GameObject
    {
    public:
        bool enabled : 1;
        HashString name;
        Transform transform;

    protected:
        GameObject* parent;

        //TO-DO: consider using smartpointers
        std::vector<GameObject*> children;
        RenderObject* renderObject;

    public:
        GameObject();
        GameObject(const char* objName);
        virtual ~GameObject();
        
        //TO-DO: Should the update of the GameObject's logic be independent
        //       from the update of its transformation matrix?
        virtual void Update();
        
        const Transform* GetTransformPtr() const;

        GameObject* GetParent() const;
        void SetParent(GameObject* parent);
        void RemoveFromCurrentParent();

        void AddChild(GameObject* child);
        void RemoveChild(GameObject* child);

        const std::vector<GameObject*>& GetChildren() const;

        void AddRenderObject(RenderObject* rObject);
        RenderObject* GetRenderObject() const;
    };


    inline const Transform* GameObject::GetTransformPtr() const
    {
        return &transform;
    }

    inline GameObject* GameObject::GetParent() const
    {
        return parent;
    }

    inline const std::vector<GameObject*>& GameObject::GetChildren() const
    {
        return children;
    }

    inline RenderObject* GameObject::GetRenderObject() const
    {
        return renderObject;
    }
}