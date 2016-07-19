#pragma once

#include <string>
#include <vector>
#include "Transform.h"
#include "../Rendering/RenderObject.h"

namespace Symphony
{
    class GameObject
    {
    public:
        Transform transform;
        std::string name;
        bool enabled;

    public:
        GameObject();
        virtual ~GameObject();
        
        //TO-DO: Should the update of the GameObject's logic be independent
        //       from the update of its transformation matrix?
        virtual void Update();
        
        void SetParent(GameObject* parent);
        void AddChild(GameObject* child);
        void RemoveChild(GameObject* child);

        const std::vector<GameObject*>& GetChildren() const;

        void AddRenderObject(RenderObject* rObject);
        RenderObject* GetRenderObject() const;

    protected:
        //TO-DO: consider using smartpointers
        std::vector<GameObject*> children;
        RenderObject* renderObject;
    };

    inline const std::vector<GameObject*>& GameObject::GetChildren() const
    {
        return children;
    }

    inline RenderObject* GameObject::GetRenderObject() const
    {
        return renderObject;
    }
}