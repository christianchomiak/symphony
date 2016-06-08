#pragma once

#include "../SymphonyEngine/Rendering/Renderer.h"
#include "../SymphonyEngine/Rendering/Shader.h"
#include "../SymphonyEngine/Scene/Light/Light.h"
#include "../SymphonyEngine/Rendering/Mesh.h"

using namespace Symphony;

class SimpleRenderer : public Renderer
{
public:
    SimpleRenderer();
    virtual ~SimpleRenderer();
    virtual void Render(const GameObject* sceneRoot, const std::vector<Camera*>& cameras, const std::vector<Light*>& lights) override;
protected:
    void RenderCamera(Camera* cam, const std::vector<const GameObject*>& objects, const std::vector<Light*>& lights);
    void PrepareObjects(const Camera* camera, const GameObject* obj, std::vector<const GameObject*>& objsOut);
};