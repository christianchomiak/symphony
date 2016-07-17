#include "Scene.h"

#include "../Debugging/Debugging.h"

Symphony::Scene::Scene()
{
    root = new SceneRoot();
    uiRoot = new SceneRoot();
    renderer = nullptr;
	id = 0;
}

Symphony::Scene::~Scene()
{
    delete root;
    delete uiRoot;
}

void Symphony::Scene::Clean()
{
    delete root;
    delete uiRoot;
    
    root = new SceneRoot();
    uiRoot = new SceneRoot();
}

void Symphony::Scene::Update(float deltaTime)
{
    root->Update();
    uiRoot->Update();
}

void Symphony::Scene::AddGameObject(GameObject* go)
{
    if (go == nullptr) return;

    root->AddChild(go);
}

void Symphony::Scene::AddGameObject(Camera* cam)
{
    if (cam == nullptr) return;
    
    cameras.push_back(cam);
    root->AddChild(cam);
}

void Symphony::Scene::AddGameObject(Light* light)
{
    if (light == nullptr) return;

    lights.push_back(light);
    root->AddChild(light);
}

void Symphony::Scene::AddGameObject(Text2D* text)
{
    if (text == nullptr) return;
    
    uiRoot->AddChild(text);
    
    int x = 1;
    x++;
}

//TO-DO: Make absolutely sure that cameras that are are registered
//       also belong to the scene tree
void Symphony::Scene::RegisterCamera(Camera* cam)
{
    if (cam == nullptr) return;
    cameras.push_back(cam);
}

//TO-DO: Make absolutely sure that lights that are are registered
//       also belong to the scene tree
void Symphony::Scene::RegisterLight(Light* light)
{
    if (light == nullptr) return;
    lights.push_back(light);
}

void Symphony::Scene::SetID(unsigned int newID)
{
    id = newID;
}
