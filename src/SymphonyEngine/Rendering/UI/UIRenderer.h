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
        void RenderUI(const std::vector<PossibleObject>& objects);
        void PrepareObjects(const GameObject* obj, std::vector<PossibleObject>& opaqueObjectsOut, bool dontIgnoreCurrentObject);
    
    protected:
        Mesh* textMesh;
        Shader* textShader;
        GLuint VAO, VBO;

        glm::mat4 uiProjectionMatrix;
    };
}