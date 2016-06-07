#pragma once

#include <vector>
#include "GameObject.h"
#include "Camera\Camera.h"

namespace Symphony
{
    class Renderer;

    class Scene
    {
        friend class SymphonyEngine;
    public:
        Scene();
        virtual ~Scene();
        
        virtual void Initialise() = 0;
        virtual void Clean() = 0;

        virtual void Update(float deltaTime);
        virtual void Render() = 0;
        void AddGameObject(GameObject*);
        void AddGameObject(Camera*);
        void RegisterCamera(Camera*);

        unsigned int GetID() const { return id; }
        std::string GetName() const { return name; }

    protected:
        GameObject* root;
        unsigned int id;
        std::string name;
        Renderer* renderer;

        std::vector<Camera*> cameras;

        void SetID(unsigned int);
    };
}