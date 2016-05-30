#pragma once

//#include <vector>
#include "GameObject.h"

namespace Symphony
{
    class Scene
    {
    public:
        Scene();
        virtual ~Scene();
        
        void Initialise();
        void Update(float deltaTime);
        void AddGameObject(GameObject*);

    protected:
        GameObject* root;
        unsigned int id;

        static unsigned int maxID;
        static unsigned int GenerateID();
    };
}