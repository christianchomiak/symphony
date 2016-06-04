#pragma once

#include "../SymphonyEngine/Rendering/Renderer.h"
#include "../SymphonyEngine/Rendering/Shader.h"
#include "../SymphonyEngine/Rendering/Mesh.h"

using namespace Symphony;

class SimpleRenderer : public Renderer
{
public:
    SimpleRenderer();
    virtual ~SimpleRenderer();
    virtual void Render() override;
protected:
    Mesh* m;
    Shader* s;
};