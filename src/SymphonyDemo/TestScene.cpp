#include "TestScene.h"

TestScene::TestScene()
{
    name = "TEST_SCENE1";
}

TestScene::~TestScene()
{
}

void TestScene::Initialise()
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

void TestScene::Clean()
{
    delete root;
}
