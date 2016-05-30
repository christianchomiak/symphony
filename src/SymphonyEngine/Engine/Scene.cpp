#include "Scene.h"

#include "../Debugging/Debugging.h"

unsigned int Symphony::Scene::maxID = 0;

Symphony::Scene::Scene()
{
    root = new GameObject();
	id = GenerateID();
}

Symphony::Scene::~Scene()
{
    delete root;
}

void Symphony::Scene::Initialise()
{
    GameObject* house = new GameObject();
    house->name = "House";
    AddGameObject(house);

    GameObject* go;

    go = new GameObject();
    go->name = "Bedroom";
    house->AddChild(go);

        GameObject* b = new GameObject();
        b->name = "Bed";
        go->AddChild(b);

        b = new GameObject();
        b->name = "Laptop";
        go->AddChild(b);

    go = new GameObject();
    go->name = "Kitchen";
    house->AddChild(go);

        b = new GameObject();
        b->name = "Food";
        go->AddChild(b);

    go = new GameObject();
    go->name = "Living Room";
    house->AddChild(go);

        b = new GameObject();
        b->name = "TV";
        go->AddChild(b);
}

void Symphony::Scene::Update(float deltaTime)
{
    Debug::Log("Updating scene #" + std::to_string(id));
    root->Update();
}

void Symphony::Scene::AddGameObject(GameObject* go)
{
    if (go == nullptr) return;

    root->AddChild(go);
}

unsigned int Symphony::Scene::GenerateID()
{
    return maxID++;
}
