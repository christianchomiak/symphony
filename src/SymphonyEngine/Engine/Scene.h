#pragma once

//#include <vector>
#include "GameObject.h"

namespace Symphony
{
    class Scene
    {
        friend class SymphonyEngine;
    public:
        Scene();
        virtual ~Scene();
        
        virtual void Initialise() = 0;
        virtual void Clean() = 0;

        void Update(float deltaTime);
        void AddGameObject(GameObject*);

        unsigned int GetID() const { return id; }
        std::string GetName() const { return name; }

    protected:
        GameObject* root;
        unsigned int id;
        std::string name;

        void SetID(unsigned int);
    };
}