#pragma once

#include "../SymphonyEngine/Engine/Scene.h"

using namespace Symphony;

class TestScene : public Scene
{
public:
    TestScene();
    virtual ~TestScene();
    
    virtual void Initialise() override;
    virtual void Clean() override;
    virtual void Update(float deltaTime) override;
};