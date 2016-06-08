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
    attributes.clear();
    uniforms.clear();

    attributes = { "position", "color", "textureCoordinate", "normal" };
    uniforms = { "modelMatrix", "viewMatrix", "projectionMatrix" };
    sEngine->LoadShader("PHONG", attributes, uniforms,
        "../../resources/Shaders/phong.vert.glsl",
        "../../resources/Shaders/phong.frag.glsl");
    attributes.clear();
    uniforms.clear();
}

int main(int argc, char* args[])
{
    sEngine = SymphonyEngine::Instance();
    
    if (!sEngine->Initialise())
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