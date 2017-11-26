#pragma once

#include <Rendering/Renderer.h>
#include <Rendering/Shader.h>
#include <Rendering/Mesh/Mesh.h>

namespace Symphony
{
    class UIRenderer : public Renderer
    {
    public:
        UIRenderer();
        virtual ~UIRenderer();
        virtual void Render(const Scene* scene) override;
    protected:
        void RenderUI(const std::vector<OrderableObject>& objects);
        void PrepareObjects(const GameObject* obj, std::vector<OrderableObject>& opaqueObjectsOut, bool dontIgnoreCurrentObject);
    
    protected:
        //TO-DO: Determine where the mesh and the shader, used for text rendering, should be.
        //       It makes sense to have them only once here to speed-up the rendering process
        //       (as it makes no sense to reload the uniforms if every single text object will
        //        be rendered using the same shader)
        Shader* textShader;

        Shader* backgroundShader;

        glm::mat4 uiProjectionMatrix;
    };
}