#pragma comment(lib, "SymphonyEngine.lib")

#include <string>
#include <iostream>

#include "../SymphonyEngine/Engine/SymphonyEngine.h"
#include "TestScene.h"

using namespace Symphony;
using namespace std;

SymphonyEngine* sEngine = nullptr;

void LoadShaders()
{
    vector<const char*> attributes;
    vector<const char*> uniforms;
        
    attributes = { "position", "color" };
    uniforms = { "modelMatrix", "viewMatrix", "projectionMatrix" };
    sEngine->LoadShader("UNLIT_COLOR", attributes, uniforms, 
                        "../../resources/Shaders/Unlit/colored.vert.glsl",
                        "../../resources/Shaders/Unlit/colored.frag.glsl");
    
    attributes = { "position", "textureCoordinate" };
    sEngine->LoadShader("UNLIT_TEXTURE", attributes, uniforms, 
                        "../../resources/Shaders/Unlit/textured.vert.glsl",
                        "../../resources/Shaders/Unlit/textured.frag.glsl");
    
    attributes = { "position", "textureCoordinate" };
    sEngine->LoadShader("TRANSPARENT", attributes, uniforms,
                        "../../resources/Shaders/Unlit/transparent.vert.glsl",
                        "../../resources/Shaders/Unlit/transparent.frag.glsl");
    attributes.clear();
    uniforms.clear();

    attributes = { "position", "color", "textureCoordinate", "normal" };
    uniforms = { "modelMatrix", "viewMatrix", "projectionMatrix" };
    sEngine->LoadShader("PHONG", attributes, uniforms,
        "../../resources/Shaders/phong.vert.glsl",
        "../../resources/Shaders/phong.frag.glsl");
    attributes.clear();
    uniforms.clear();

    attributes = { "position" };
    uniforms = { "modelMatrix", "viewMatrix", "projectionMatrix", "nearPlane", "farPlane"};
    sEngine->LoadShader("DEPTH", attributes, uniforms,
        "../../resources/Shaders/depthtest.vert.glsl",
        "../../resources/Shaders/depthtest.frag.glsl");
    attributes.clear();
    uniforms.clear();
    
    attributes = { "position", "textureCoordinate" };
    sEngine->LoadShader("SIMPLE", attributes, uniforms,
        "../../resources/Shaders/Unlit/simple.vert.glsl",
        "../../resources/Shaders/Unlit/simple.frag.glsl");
    attributes.clear();
    uniforms.clear();
}

int main(int argc, char* args[])
{
    sEngine = SymphonyEngine::Instance();
    
    Window::WindowProperties wProperties = Window::WindowProperties();
    wProperties.cursorMode = Window::CursorMode::DISABLED;
    wProperties.decorated = true;
    wProperties.fullscreen = false;
    wProperties.width = 1280;
    wProperties.height = 720;
    wProperties.maximised = false;
    wProperties.resizeable = true;
    wProperties.title = "Symphony Engine demo";
    wProperties.switchableToOtherModes = false;

    if (!sEngine->Initialise(wProperties))
    {
        std::cout << "Error trying to initialise Symphony Engine" << std::endl;
        system("pause");
        return -1;
    }

    LoadShaders();

    //std::cout << glGetString(GL_VERSION) << std::endl;
    sEngine->AddScene(new TestScene());
    sEngine->Run();
    sEngine->Shutdown();
    
    //system("pause");
    
    return 0;
}