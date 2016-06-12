#pragma once

#include "../SymphonyEngine/Scene/Scene.h"

using namespace Symphony;

class TestScene : public Scene
{
public:
    TestScene();
    virtual ~TestScene();
    
    virtual void Initialise() override;
    virtual void Clean() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;

protected:
    Mesh* textMesh;
    Shader* textShader;
    GLuint VAO, VBO;

    Text* txt;
};