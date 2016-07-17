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
    virtual void Render(const Scene* scene) override;
protected:
    void RenderCamera(Camera* cam, const std::vector<PossibleObject>& objects, const std::vector<Light*>& lights);
    void PrepareObjects(const Camera* camera, const GameObject* obj, std::vector<PossibleObject>& opaqueObjectsOut, std::vector<PossibleObject>& transparentObjectsOut);
};