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

    Debug::Log("Added a GAMEOBJECT");

    root->AddChild(go);
}

void Symphony::Scene::AddGameObject(Camera* go)
{
    if (go == nullptr) return;
    
    Debug::Log("Added a CAMERA");
    cameras.push_back(go);

    root->AddChild(go);
}

void Symphony::Scene::SetID(unsigned int newID)
{
    id = newID;
}
