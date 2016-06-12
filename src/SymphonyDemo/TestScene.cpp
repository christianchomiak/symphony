#include "TestScene.h"

#include "SimpleRenderer.h"
#include "ComplexRenderer.h"
#include "../SymphonyEngine/Debugging/Debugging.h"
#include "../SymphonyEngine/Input/InputManager.h"

#include "../SymphonyEngine/Scene/Camera/PerspectiveCamera.h"
#include "../SymphonyEngine/Scene/Camera/OrthographicCamera.h"

#include "../SymphonyEngine/Scene/Light/PointLight.h"
#include "../SymphonyEngine/Scene/Light/DirectionalLight.h"
#include "../SymphonyEngine/Scene/Light/Spotlight.h"

#include "FreeRoamCamera.h"

#include "../SymphonyEngine/Rendering/TextureManager.h"

TestScene::TestScene()
{
    name = "TEST_SCENE1";
}

TestScene::~TestScene()
{
    delete renderer;
}

void TestScene::Initialise()
{
    renderer = new ComplexRenderer();

    FreeRoamCamera* cam = new FreeRoamCamera();
    cam->name = "Camera";
    //RegisterCamera(cam);
    //emptyGo->AddChild(cam);
    cam->transform.Translate(0, 150, -30);
    //cam->transform.Rotate(0, 90, 0);
    AddGameObject(cam);
    cam->SetSkybox(TextureManager::LoadSkybox("SKY",
        "../../resources/Textures/Skybox/right.jpg",
        "../../resources/Textures/Skybox/left.jpg",
        "../../resources/Textures/Skybox/top.jpg",
        "../../resources/Textures/Skybox/bottom.jpg",
        "../../resources/Textures/Skybox/back.jpg",
        "../../resources/Textures/Skybox/front.jpg"),
        Shader::GetShader("SKYBOX"));

    Light* light;

    int lightType = 0;
    if (lightType < 0)
    {
        light = new PointLight(glm::vec3(0.0f, 0, 0.0f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
            50.f, 1.0f, 0.014f, 0.0007f);
        light->name = "Point Light";

        cam->AddChild(light);
        RegisterLight(light);
    }
    else if (lightType == 0)
    {
        light = new DirectionalLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f));
        light->name = "Directional Light";
        /*cam->AddChild(dLight);
        RegisterLight(dLight);*/

        AddGameObject(light);
        light->transform.SetLocalPosition(0, 100, -10.f);
        light->transform.SetLocalRotation(45, 0, 0);
    }
    else
    {
        light = new Spotlight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
            12.5f, 15.f, 1.0f, 0.007, 0.0002f);
        light->name = "Spotlight";

        cam->AddChild(light);
        RegisterLight(light);
        light->transform.SetLocalRotation(0, 180, 0);
        /*AddGameObject(light);
        light->transform.SetLocalPosition(0, 50, -10.f);
        light->transform.SetLocalRotation(15, 0, 0);*/
    }

    GameObject* coord = new GameObject();
    coord->name = "Coordinate System";
    //AddGameObject(coord);
    coord->AddRenderObject(new RenderObject(Mesh::CoordinateSystem(), Texture(), Shader::GetShader("UNLIT_COLOR")));
    //coord->transform.SetLocalPosition(0, 150, -10.f);
    light->AddChild(coord);

    GameObject* cube = new GameObject();
    cube->name = "Cube";
    AddGameObject(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            TextureManager::LoadTexture("../../resources/Textures/window.png", Texture::WrappingType::CLAMP, Texture::FilteringType::LINEAR, true, Texture::Transparency::SEMI),
            Shader::GetShader("UNLIT_TEXTURE")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);

    //GetPosition doesn't work at this stage because the scene tree hasn't been updated yet.
    //TO-DO: find a workaround to this issue.
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());

    cube->transform.Translate(0, 0, 5);
    cube->transform.Scale(5.f);
    /*cube->GetRenderObject()->material = Material(glm::vec3(1.f, 1.f, 1.f),          //Ambient
    glm::vec3(1.f, 1.f, 1.f),          //Diffuse
    glm::vec3(1.f, 1.f, 1.f),          //Specular
    0.1f);                             //Shininess
    */

    cube = new GameObject();
    cube->name = "Cube2";
    AddGameObject(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            Texture(), //TextureManager::LoadTexture("../../resources/Textures/window.png", Texture::WrappingType::CLAMP, Texture::FilteringType::LINEAR, true, Texture::Transparency::SEMI),
            Shader::GetShader("REFLECTIVE")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());
    cube->transform.Translate(0, 0, 15);
    cube->transform.Scale(5.f);

    cube = new GameObject();
    cube->name = "Cube3";
    AddGameObject(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            TextureManager::LoadTexture("../../resources/Textures/grass.png", Texture::WrappingType::CLAMP, Texture::FilteringType::LINEAR, true, Texture::Transparency::FULL),
            Shader::GetShader("TRANSPARENT")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());
    cube->transform.Translate(0, 0, 25);
    cube->transform.Scale(5.f);



    GameObject* hMap = new GameObject();
    hMap->name = "Height Map";
    AddGameObject(hMap);
    hMap->AddRenderObject(
        new RenderObject(Mesh::HeightMap("../../resources/Textures/hm2.png", 16.f, 16.f, 1000.f),
            TextureManager::LoadTexture("../../resources/Textures/hmTexture.jpg", Texture::WrappingType::REPEAT, Texture::FilteringType::TRILINEAR),
            Shader::GetShader("PHONG")));
    hMap->transform.SetLocalPosition(0, 0, -100);
    hMap->transform.Scale(0.1f);


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
        renderer->Render(root, cameras, lights);
    }
}
