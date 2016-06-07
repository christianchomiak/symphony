#include "TestScene.h"

#include "SimpleRenderer.h"
#include "../SymphonyEngine/Debugging/Debugging.h"
#include "../SymphonyEngine/Input/InputManager.h"

#include "../SymphonyEngine/Engine/Camera/PerspectiveCamera.h"
#include "../SymphonyEngine/Engine/Camera/OrthographicCamera.h"

#include "FreeRoamCamera.h"

#include "../SymphonyEngine/Rendering/TextureManager.h"

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
    GameObject* coord = new GameObject();
    coord->name = "Coordinate System";
    AddGameObject(coord);
    coord->AddRenderObject(new RenderObject(Mesh::CoordinateSystem(), Texture(), Shader::GetShader("UNLIT_COLOR")));
    //coord->transform.SetLocalPosition(0, 0, 10.f);
    
    GameObject* hMap = new GameObject();
    hMap->name = "Height Map";
    AddGameObject(hMap);
    hMap->AddRenderObject(
        new RenderObject(Mesh::HeightMap("../../resources/Textures/hm.png", 16.f, 16.f, 1000.f),
            TextureManager::LoadTexture("../../resources/Textures/hmTexture.jpg", Texture::WrappingType::REPEAT, Texture::FilteringType::TRILINEAR),
            Shader::GetShader("UNLIT_TEXTURE")));
    hMap->transform.SetLocalPosition(0, 0, -100);
    hMap->transform.Scale(0.1f);

   /* GameObject* emptyGo = new GameObject();
    AddGameObject(emptyGo);
    emptyGo->transform.Translate(2.5f, 0, 5);
    emptyGo->transform.Rotate(0, 25, 0);*/
    

    FreeRoamCamera* cam = new FreeRoamCamera();
    cam->name = "Camera";
    //RegisterCamera(cam);
    //emptyGo->AddChild(cam);
    cam->transform.Translate(0, 150, 5);
    cam->transform.Rotate(0, 90, 0);
    AddGameObject(cam);

    cube = new GameObject();
    cube->name = "Cube";
    AddGameObject(cube);
    //cam->AddChild(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            //TextureManager::LoadTexture("../../resources/Textures/face.png", Texture::WrappingType::CLAMP, Texture::FilteringType::LINEAR),
            Shader::GetShader("UNLIT_COLOR")));
    //emptyGo->AddChild(cube);
    cube->transform.SetLocalPosition(0, 150, -10.f);
    cube->GetRenderObject()->SetBoundingRadius(1.5f);



    /*PerspectiveCamera* cam = new PerspectiveCamera(45.f);
    //OrthographicCamera* cam = new OrthographicCamera(-1, 1, 1, -1);
    cam->name = "Camera";
    AddGameObject(cam);*/
}

void TestScene::Clean()
{
    delete root;
}

void TestScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    /*const Keyboard* keyboard = InputManager::GetKeyboard();
    
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
    if (keyboard->KeyPressed(Keyboard::KEY_ARROW_UP)) go->transform.Rotate(-speed * deltaTime, 0, 0);
    else if (keyboard->KeyPressed(Keyboard::KEY_ARROW_DOWN)) go->transform.Rotate(speed * deltaTime, 0, 0);
    else if (keyboard->KeyPressed(Keyboard::KEY_ARROW_LEFT)) go->transform.Rotate(0, -speed * deltaTime, 0);
    else if (keyboard->KeyPressed(Keyboard::KEY_ARROW_RIGHT)) go->transform.Rotate(0, speed * deltaTime, 0);

    if (keyboard->KeyPressed(Keyboard::KEY_W))
    {
        
    }
    
    glm::vec3 dir;
    if (keyboard->KeyPressed(Keyboard::KEY_U))
    {
        dir = go->transform.Up();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_D))
    {
        dir = -go->transform.Up();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_F))
    {
        dir = go->transform.Forward();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_B))
    {
        dir = -go->transform.Forward();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_L))
    {
        dir = -go->transform.Right();
    }
    else if (keyboard->KeyPressed(Keyboard::KEY_R))
    {
        dir = go->transform.Right();
    }

    go->transform.Translate(dir.x * deltaTime, dir.y * deltaTime, dir.z * deltaTime);

    if (mouse->ButtonDown(Mouse::BUTTON_LEFT)) go->enabled = !go->enabled;*/
}

void TestScene::Render()
{
    if (renderer)
    {
        renderer->Render(cameras, root);
    }
}
