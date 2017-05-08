#pragma comment(lib, "SymphonyEngine.lib")

#include <memory>

#include "../SymphonyEngine/Engine/SymphonyEngine.h"
#include "TestScene.h"

#include "../SymphonyEngine/Utilities/HashString.h"

using namespace std;
using namespace Symphony;

SymphonyEngine* sEngine = nullptr;

void LoadShaders()
{
    /*vector<const char*> attributes;
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
    uniforms = { "modelMatrix", "viewMatrix", "projectionMatrix", "nearPlane", "farPlane" };
    sEngine->LoadShader("DEPTH", attributes, uniforms,
        "../../resources/Shaders/depthtest.vert.glsl",
        "../../resources/Shaders/depthtest.frag.glsl");
    attributes.clear();
    uniforms.clear();

    attributes = { "position", "textureCoordinate" };
    sEngine->LoadShader("SIMPLE", attributes, uniforms,
        "../../resources/Shaders/PostProcess/simple.vert.glsl",
        "../../resources/Shaders/PostProcess/simple.frag.glsl");
    attributes.clear();
    uniforms.clear();

    sEngine->LoadShader("SKYBOX", attributes, uniforms,
        "../../resources/Shaders/Unlit/skybox.vert.glsl",
        "../../resources/Shaders/Unlit/skybox.frag.glsl");
    attributes.clear();
    uniforms.clear();

    sEngine->LoadShader("REFLECTIVE", attributes, uniforms,
        "../../resources/Shaders/reflection.vert.glsl",
        "../../resources/Shaders/reflection.frag.glsl");
    attributes.clear();
    uniforms.clear();

    sEngine->LoadShader("TEXT", attributes, uniforms,
        "../../resources/Shaders/text.vert.glsl",
        "../../resources/Shaders/text.frag.glsl");
    attributes.clear();
    uniforms.clear();*/

}

void TestGround()
{
    std::cout.setf(std::ios::boolalpha);

    HashString hs1 = "Test";
    std::string s1 = "Test";
    const char* s2 = "Test";
    hs1 = s2;
    std::cout << "HS1 == HS2: " << (hs1 == s2) << std::endl;
}

int main(int argc, char* args[])
{
    sEngine = SymphonyEngine::Instance();
    
    const char* xmlConfig = "../../resources/SymphonyConfig.xml";
    const char* commandLineArgs = (args == nullptr || argc < 2) ? nullptr : args[1];

    if (!sEngine->Initialise(xmlConfig, commandLineArgs))
    {
        std::cout << "Error trying to initialise Symphony Engine" << std::endl;
        system("pause");
        return -1;
    }

    sEngine->LoadShaders("../../resources/shaders.xml");
    sEngine->AddScene(new TestScene());
    sEngine->Run();
    sEngine->Shutdown();

    system("pause");

    return 0;
}