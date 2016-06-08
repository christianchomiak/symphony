#pragma once

#include <vector>
#include "GameObject.h"
#include "Camera\Camera.h"
#include "Light\Light.h"

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
        void AddGameObject(Light*);

        void RegisterCamera(Camera*);
        void RegisterLight(Light*);

        unsigned int GetID() const { return id; }
        std::string GetName() const { return name; }

    protected:
        GameObject* root;
        unsigned int id;
        std::string name;
        Renderer* renderer;

        std::vector<Camera*> cameras;
        std::vector<Light*> lights;

        void SetID(unsigned int);
    };
}