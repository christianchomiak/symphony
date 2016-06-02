#include "Scene.h"

#include "../Debugging/Debugging.h"

Symphony::Scene::Scene()
{
    root = new GameObject();
	id = 0;
}

Symphony::Scene::~Scene()
{
    delete root;
}

void Symphony::Scene::Update(float deltaTime)
{
    Debug::Log("Updating scene #" + std::to_string(id) + " (" + name + ")");
    root->Update();
}

void Symphony::Scene::AddGameObject(GameObject* go)
{
    if (go == nullptr) return;

    root->AddChild(go);
}

void Symphony::Scene::SetID(unsigned int newID)
{
    id = newID;
}
