#include "TestScene.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "SimpleRenderer.h"
#include "ComplexRenderer.h"
#include "FreeRoamCamera.h"

#include "../SymphonyEngine/Debugging/Debugging.h"
#include "../SymphonyEngine/Input/InputManager.h"

#include "../SymphonyEngine/Scene/Camera/PerspectiveCamera.h"
#include "../SymphonyEngine/Scene/Camera/OrthographicCamera.h"

#include "../SymphonyEngine/Scene/Light/PointLight.h"
#include "../SymphonyEngine/Scene/Light/DirectionalLight.h"
#include "../SymphonyEngine/Scene/Light/Spotlight.h"

#include "../SymphonyEngine/Rendering/Textures/TextureManager.h"

#include "../SymphonyEngine/Rendering/UI/Font.h"

#include "../SymphonyEngine/Macros/ResourcesMacros.h"
#include "../SymphonyEngine/Macros/VectorMacros.h"
#include "FPSCounterObject.h"

#include <imgui/imgui.h>

TestScene::TestScene()
{
    name = "TEST_SCENE_1";
}

TestScene::~TestScene()
{
    delete renderer;
    delete uiRenderer;
}

void TestScene::Initialise()
{
    renderer = new ComplexRenderer();
    uiRenderer = new UIRenderer();

    FreeRoamCamera* cam = new FreeRoamCamera();
    cam->name = "Camera";
    //RegisterCamera(cam);
    //emptyGo->AddChild(cam);
    cam->transform.Translate(0, 150, -30);
    //cam->transform.Rotate(0, 90, 0);
    AddGameObject(cam);
    cam->SetSkybox(TextureManager::LoadSkybox("SKY",
         RESOURCES_FOLDER(Textures/Skybox/right.jpg ),
         RESOURCES_FOLDER(Textures/Skybox/left.jpg  ),
         RESOURCES_FOLDER(Textures/Skybox/top.jpg   ),
         RESOURCES_FOLDER(Textures/Skybox/bottom.jpg),
         RESOURCES_FOLDER(Textures/Skybox/back.jpg  ),
         RESOURCES_FOLDER(Textures/Skybox/front.jpg )),
         Shader::GetShader("SKYBOX"));

    Light* light;

    int lightType = 0;
    if (lightType < 0)
    {
        light = new PointLight(V3_ZERO, V3_ONE, V3_ZERO, 50.f, 1.0f, 0.014f, 0.0007f);
        light->name = "Point Light";

        cam->AddChild(light);
        RegisterLight(light);
    }
    else if (lightType == 0)
    {
        light = new DirectionalLight(glm::vec3(0.1f, 0.1f, 0.1f), V3_ONE, V3_ZERO);
        light->name = "Directional Light";
        /*cam->AddChild(dLight);
        RegisterLight(dLight);*/

        AddGameObject(light);
        light->transform.SetLocalPosition(0, 100, -10.f);
        light->transform.SetLocalRotation(45, 0, 0);
    }
    else
    {
        light = new Spotlight(glm::vec3(0.1f, 0.1f, 0.1f), V3_ONE, V3_ZERO,
                              12.5f, 15.f, 1.0f, 0.007f, 0.0002f);
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
            TextureManager::LoadTexture(RESOURCES_FOLDER(Textures/window.png),
                                        Texture::WrappingType::CLAMP,
                                        Texture::FilteringType::LINEAR,
                                        true, Texture::Transparency::SEMI),
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
            TextureManager::LoadTexture(RESOURCES_FOLDER(Textures/grass.png), Texture::WrappingType::CLAMP, Texture::FilteringType::NEAREST, true, Texture::Transparency::FULL),
            Shader::GetShader("TRANSPARENT")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());
    cube->transform.Translate(0, 0, 25);
    cube->transform.Scale(5.f);



    GameObject* hMap = new GameObject();
    hMap->name = "Height Map";
    AddGameObject(hMap);
    hMap->AddRenderObject(
        new RenderObject(Mesh::HeightMap(RESOURCES_FOLDER(Textures/hm2.png), 16.0f, 16.0f, 1000.0f),
            TextureManager::LoadTexture(RESOURCES_FOLDER(Textures/hmTexture.jpg), Texture::WrappingType::REPEAT, Texture::FilteringType::TRILINEAR),
            Shader::GetShader("PHONG")));
    hMap->transform.SetLocalPosition(0, 0, -100);
    hMap->transform.Scale(0.1f);


    /*PerspectiveCamera* cam = new PerspectiveCamera(45.f);
    //OrthographicCamera* cam = new OrthographicCamera(-1, 1, 1, -1);
    cam->name = "Camera";
    AddGameObject(cam);*/

    /*txt = new Text("String", glm::vec3(Screen::Width() * 0.5f, Screen::Height() * 0.5f, 0.5f),
                   glm::vec3(1.f, 1.f, 1.f), 1.f, Text::HorizontalCentering::HCENTER);
    AddText(txt);*/
    
    
    //TEXT
    Font* arial = Font::Find("Arial");
    
    Text2D* txtObject;
    glm::vec3 pos = glm::vec3(Screen::Width() * 0.5f, Screen::Height() * 0.5f, 0.0f);
    float scale = 1.f;
    
    Text text(arial, "String", Color::RED, scale, Text::Alignment::CENTER_LEFT);
    text.SetFont(arial);
    text.bgColor = Color::BLACK_ALPHA;

    txtObject = new Text2D(text);
    txtObject->transform.SetPosition(pos);
    txtObject->transform.Rotate(0.0f, 0.0f, -90.0f);
    AddGameObject(txtObject);

    /////

    text.fgColor = Color::GREEN;
    text.SetAlignment(Text::Alignment::CENTER);

    txtObject = new Text2D(text);
    txtObject->transform.SetPosition(pos);
    txtObject->transform.Rotate(0.0f, 0.0f, 90.0f);
    AddGameObject(txtObject);

    /////

    text.fgColor = Color::BLUE;
    text.SetAlignment(Text::Alignment::CENTER_RIGHT);

    txtObject = new Text2D(text);
    txtObject->transform.SetPosition(pos);
    AddGameObject(txtObject);

    ////FPS-counter
    text.fgColor = Color::WHITE;
    text.SetAlignment(Text::Alignment::BOTTOM_LEFT);
    
    txtObject = new FPSCounterObject(text);
    txtObject->transform.SetPosition(pos);
    AddGameObject(txtObject);
}

void TestScene::Clean()
{
    Scene::Clean();

    /*for (auto t : uiRoot)
    {
        delete t;
    }*/
}

void TestScene::Update()
{
    Scene::Update();

    //txt->content = std::to_string(deltaTime).c_str();

    /*if (InputManager::GetMouse().ButtonPressed(MButton::BTN_LEFT))
    {
        Debug::Log("Mouse");
    }*/
}

void TestScene::Render()
{
    if (renderer)
    {
        renderer->Render(this); // root, cameras, lights);
    }
    
    if (uiRenderer)
    {
        uiRenderer->Render(this);
    }
}
