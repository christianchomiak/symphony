#include "TestScene.h"

#include "SimpleRenderer.h"
#include "../SymphonyEngine/Debugging/Debugging.h"
#include "../SymphonyEngine/Input/InputManager.h"

#include "../SymphonyEngine/Engine/Camera/PerspectiveCamera.h"
#include "../SymphonyEngine/Engine/Camera/OrthographicCamera.h"

TestScene::TestScene()
{
    name = "TEST_SCENE1";
    renderer = new SimpleRenderer();
}

TestScene::~TestScene()
{
    delete renderer;
}

void TestScene::Initialise()
{
    coord = new GameObject();
    coord->name = "Coordinate System";
    AddGameObject(coord);
    coord->mesh = Mesh::CoordinateSystem();
    //coord->mesh = Mesh::Quad();
    coord->transform.SetLocalPosition(0, 0, -2.5f);
    //coord->transform.SetLocalRotation(10, 45, 0);

    /*coord = new GameObject();
    coord->name = "Object";
    AddGameObject(coord);
    coord->mesh = Mesh::Quad();
    coord->transform.SetLocalPosition(0, 0, -0.5f);*/
    
    PerspectiveCamera* cam = new PerspectiveCamera(45.f);
    //OrthographicCamera* cam = new OrthographicCamera(-1, 1, 1, -1);
    cam->name = "Camera";
    AddGameObject(cam);
}

void TestScene::Clean()
{
    delete root;
}

void TestScene::Update(float deltaTime)
{
    //Debug::Log("Updating scene #" + std::to_string(id) + " (" + name + ")");
    Scene::Update(deltaTime);

    const Keyboard* keyboard = InputManager::GetKeyboard();
    /*if (keyboard->KeyDown(Keyboard::KEY_D ))
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
    }*/
    
    const Mouse* mouse = InputManager::GetMouse();
    if (mouse->ButtonDown(Mouse::BUTTON_LEFT)) Debug::Log("LEFT BUTTON");
    if (mouse->ButtonDown(Mouse::BUTTON_RIGHT)) Debug::Log("RIGHT BUTTON");
    if (mouse->ButtonDown(Mouse::BUTTON_MIDDLE)) Debug::Log("MIDDLE BUTTON");
    if (mouse->ButtonDown(Mouse::BUTTON_4)) Debug::Log("BUTTON 4");
    if (mouse->ButtonDown(Mouse::BUTTON_5)) Debug::Log("BUTTON 5");
    if (mouse->ButtonDown(Mouse::BUTTON_6)) Debug::Log("BUTTON 6");
    if (mouse->ButtonDown(Mouse::BUTTON_7)) Debug::Log("BUTTON 7");
    if (mouse->ButtonDown(Mouse::BUTTON_8)) Debug::Log("BUTTON 8");
    
    float speed = 20.f;
    if (keyboard->KeyPressed(Keyboard::KEY_ARROW_UP)) coord->transform.Rotate(-speed * deltaTime, 0, 0);
    else if (keyboard->KeyPressed(Keyboard::KEY_ARROW_DOWN)) coord->transform.Rotate(speed * deltaTime, 0, 0);
    else if (keyboard->KeyPressed(Keyboard::KEY_ARROW_LEFT)) coord->transform.Rotate(0, -speed * deltaTime, 0);
    else if (keyboard->KeyPressed(Keyboard::KEY_ARROW_RIGHT)) coord->transform.Rotate(0, speed * deltaTime, 0);

    if (keyboard->KeyPressed(Keyboard::KEY_W))
    {
        
    }
    
    glm::vec3 dir;
    if (keyboard->KeyPressed(Keyboard::KEY_U))
    {
        dir = coord->transform.Up();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_D))
    {
        dir = -coord->transform.Up();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_F))
    {
        dir = coord->transform.Forward();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_B))
    {
        dir = -coord->transform.Forward();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_L))
    {
        dir = -coord->transform.Right();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_R))
    {
        dir = coord->transform.Right();
    }

    coord->transform.Translate(dir.x * deltaTime, dir.y * deltaTime, dir.z * deltaTime);
}

void TestScene::Render()
{
    if (renderer)
    {
        renderer->Render(cameras, root);
    }
}
