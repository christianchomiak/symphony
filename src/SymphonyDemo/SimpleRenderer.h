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
    virtual void Render(const std::vector<Camera*>& cameras, const GameObject* sceneRoot) override;
protected:
    void RenderCamera(Camera* cam, const std::vector<const GameObject*>& objects);
    void PrepareObjects(const GameObject* obj, std::vector<const GameObject*>& objsOut);
};