#pragma once

#include <vector>

#include <Utilities/HashString.h>

#include <SymphonyGlobal.h>
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
        Scene(HashString sceneId);
        virtual ~Scene();
        
        virtual void Initialise() = 0;
        virtual void Clean();

        virtual void Update();
        virtual void Render() = 0;

        //TO-DO: What if these functions receive an optional parameter representing the parent of the object?
        void AddGameObject(GameObject*);
        void AddGameObject(Camera*);
        void AddGameObject(Light*);
        void AddGameObject(Text2D*);

        void RegisterCamera(Camera*);
        void RegisterLight(Light*);

        HashString GetID() const;
        
        const SceneRoot* GetSceneRoot() const;

        const SceneRoot* GetSceneUIRoot() const;

        const std::vector<Camera*>& Cameras() const;

        const std::vector<Light*>& Lights() const;

#ifdef _DEBUG
        const char* GetName() const;
#endif

    protected:
        HashString id;
        SceneRoot *root, *uiRoot;
        Renderer* renderer;
        
        //std::vector<Text2D*> uiRoot;
        std::vector<Camera*> cameras;
        std::vector<Light*>  lights;

        void SetId(const char*);
    };



    inline HashString Scene::GetID() const
    {
        return id;
    }
    
    inline const SceneRoot* Scene::GetSceneRoot() const
    {
        return root;
    }

    inline const SceneRoot* Scene::GetSceneUIRoot() const
    {
        return uiRoot;
    }

    inline const std::vector<Camera*>& Scene::Cameras() const
    {
        return cameras;
    }

    inline const std::vector<Light*>& Scene::Lights() const
    {
        return lights;
    }

#ifdef _DEBUG
    inline const char* Scene::GetName() const
    {
        return id.GetCString();
    }
#endif
}