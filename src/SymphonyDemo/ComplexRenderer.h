#pragma once

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files

#include "../SymphonyEngine/Rendering/Renderer.h"
#include "../SymphonyEngine/Rendering/Shader.h"
#include "../SymphonyEngine/Scene/Light/Light.h"
#include "../SymphonyEngine/Rendering/Mesh/Mesh.h"

using namespace Symphony;

class ComplexRenderer : public Renderer
{
public:
    ComplexRenderer();
    virtual ~ComplexRenderer();
    virtual void Render(const Scene* scene) override;
protected:
    void RenderCamera(Camera* cam, const std::vector<OrderableObject>& objects, const std::vector<Light*>& lights);
    void PrepareObjects(const Camera* camera, const GameObject* obj, std::vector<OrderableObject>& opaqueObjectsOut, std::vector<OrderableObject>& transparentObjectsOut);

protected:
    GLuint frameBuffer;
    GLuint bufferColourTexture;
    GLuint bufferDepthTexture;
    
    //(Render Buffer Object)
    //This is an alternative to using traditional textures such as `bufferDepthTexture`.
    //RBOs are write-only, making them great for stencil and depth as it's unusual to sample (read) from them.
    //In case such operations are necessary, the RBO should be ditched in favour of `bufferDepthTexture`.
    GLuint rbo;

    Mesh* screenQuad;
    Shader* screenShader; //TO-DO: Handle case when shader fails loading
};