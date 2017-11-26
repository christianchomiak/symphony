#include "Scene.h"

#include <Debugging/Debugging.h>

using namespace Symphony;

Scene::Scene()
    : Scene(0u)
{
}

Scene::Scene(HashString sceneId)
    : id(sceneId),
      renderer(nullptr)
{
    root = new SceneRoot();
    uiRoot = new SceneRoot();
}

Scene::~Scene()
{
    delete root;
    delete uiRoot;
}

void Scene::Clean()
{
    delete root;
    delete uiRoot;
    
    root   = new SceneRoot();
    uiRoot = new SceneRoot();
}

void Scene::Update()
{
    root->Update();
    uiRoot->Update();
}

void Scene::AddGameObject(GameObject* go)
{
    AssertF(go, "Trying to add a null GameObject to Scene [%s]", id.GetCString());

    if (go != nullptr)
    {
        root->AddChild(go);
    }
}

void Scene::AddGameObject(Camera* cam)
{
    AssertF(cam, "Trying to add a null Camera to Scene [%s]", id.GetCString());

    if (cam)
    {
        cameras.push_back(cam);
        root->AddChild(cam);
    }
}

void Scene::AddGameObject(Light* light)
{
    AssertF(light, "Trying to add a null Light to Scene [%s]", id.GetCString());

    if (light)
    {
        lights.push_back(light);
        root->AddChild(light);
    }
}

void Scene::AddGameObject(Text2D* text)
{
    AssertF(text, "Trying to add a null Text2D to Scene [%s]", id.GetCString());

    if (text)
    {
        uiRoot->AddChild(text);
    }
}

//TO-DO: Make absolutely sure that cameras that are are registered
//       also belong to the scene tree
void Scene::RegisterCamera(Camera* cam)
{
    if (cam == nullptr) return;
    cameras.push_back(cam);
}

//TO-DO: Make absolutely sure that lights that are are registered
//       also belong to the scene tree
void Scene::RegisterLight(Light* light)
{
    if (light == nullptr) return;
    lights.push_back(light);
}

void Scene::SetId(const char* newID)
{
    id = newID;
}
