#pragma once

#include <string>
#include <vector>
#include "Transform.h"

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
        
        virtual void Update();

        void AddChild(GameObject* child);
        void RemoveChild(GameObject* child);

        void SetParent(GameObject* parent);
        
    protected:
        //TO-DO: consider using smartpointers
        std::vector<GameObject*> children;
    };
}