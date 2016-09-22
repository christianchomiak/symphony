#pragma once

#include <vector>
#include "GameObject.h"
#include "SceneRoot.h"
#include "Camera/Camera.h"
#include "Light/Light.h"
#include "Text/Text2D.h"

namespace Symphony
{
    class Renderer;

    class Scene
    {
        friend class SymphonyEngine;
        friend class Renderer;
    public:
        Scene();
        virtual ~Scene();
        
        virtual void Initialise() = 0;
        virtual void Clean();

        virtual void Update(float deltaTime);
        virtual void Render() = 0;

        //TO-DO: What if these functions receive an optional parameter representing the parent of the object?
        void AddGameObject(GameObject*);
        void AddGameObject(Camera*);
        void AddGameObject(Light*);
        void AddGameObject(Text2D*);

        void RegisterCamera(Camera*);
        void RegisterLight(Light*);

        inline unsigned int GetID() const { return id; }
        inline std::string GetName() const { return name; }

        inline const SceneRoot* GetSceneRoot() const
        {
            return root;
        }
        inline const SceneRoot* GetSceneUIRoot() const
        {
            return uiRoot;
        }
        inline const std::vector<Camera*>& Cameras() const
        {
            return cameras;
        }
        inline const std::vector<Light*>& Lights() const
        {
            return lights;
        }

    protected:
        SceneRoot *root, *uiRoot;
        unsigned int id;
        std::string name;
        Renderer* renderer;
        
        //std::vector<Text2D*> uiRoot;
        std::vector<Camera*> cameras;
        std::vector<Light*> lights;

        void SetID(unsigned int);
    };
}