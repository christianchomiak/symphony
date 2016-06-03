#include "TestScene.h"

#include "../SymphonyEngine/Debugging/Debugging.h"
#include "../SymphonyEngine/Input/InputManager.h"

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

void TestScene::Update(float deltaTime)
{
    //Debug::Log("Updating scene #" + std::to_string(id) + " (" + name + ")");
    Scene::Update(deltaTime);

    const Keyboard* keyboard = InputManager::Instance()->GetKeyboard();
    if (keyboard->KeyDown(Keyboard::KEY_D ))
    {
        Debug::Log("`D` DOWN");
    }
    else if (keyboard->KeyUp(Keyboard::KEY_U))
    {
        Debug::Log("`U` UP");
    }
    else if (keyboard->KeyHold(Keyboard::KEY_H))
    {
        Debug::Log("`H` HELD");
    }

    if (keyboard->KeyPressed(Keyboard::KEY_Q))
    {
        Debug::Log("`Q` PRESSED");
    }
}
