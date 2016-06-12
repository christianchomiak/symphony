#include "Scene.h"

#include "../Debugging/Debugging.h"

Symphony::Scene::Scene()
{
    root = new GameObject();
    renderer = nullptr;
	id = 0;
}

Symphony::Scene::~Scene()
{
    delete root;
}

void Symphony::Scene::Update(float deltaTime)
{
    root->Update();
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

void Symphony::Scene::AddText(Text* text)
{
    if (text == nullptr) return;

    uiText.push_back(text);
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
