#pragma once

#include "../Renderer.h"
#include "../Shader.h"
#include "../Mesh.h"

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
        Mesh* textMesh;
        Shader* textShader;
        GLuint VAO, VBO;

        glm::mat4 uiProjectionMatrix;
    };
}