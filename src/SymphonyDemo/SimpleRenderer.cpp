#include "SimpleRenderer.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

SimpleRenderer::SimpleRenderer()
{
}

SimpleRenderer::~SimpleRenderer()
{
}

void SimpleRenderer::Render(const std::vector<Camera*>& cameras, const GameObject* sceneRoot)
{
    std::vector<const GameObject*> objs;
    
    for (Camera* cam : cameras)
    {
        PrepareObjects(cam, sceneRoot, objs);
        //std::cout << "Rendering " << objs.size() << " object(s)" << std::endl;
        RenderCamera(cam, objs);
        objs.clear();
    }
}

void SimpleRenderer::RenderCamera(Camera* cam, const std::vector<const GameObject*>& objects)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 P = cam->ProjectionMatrix(); //glm::mat4(1);
    glm::mat4 V = cam->ViewMatrix();
    
    for (auto go : objects)
    {
        //std::cout << "Rendering object: " << go->name << std::endl;

        auto rObject = go->GetRenderObject();
        Shader& ss = *(rObject->GetShader());
        ss.Use();
        
        if (rObject->GetTexture().id > 0)
        {
            glActiveTexture(GL_TEXTURE0);
            ProcessTexture(rObject->GetTexture());
        }

        glUniformMatrix4fv(ss("MVP"), 1, GL_FALSE, glm::value_ptr(P*V*go->transform.GetWorldTransformMatrix()));
        rObject->GetMesh()->Render();

        ss.Release();
    }
    glActiveTexture(0);
}

void SimpleRenderer::PrepareObjects(const Camera* camera, const GameObject* obj, std::vector<const GameObject*>& objsOut)
{
    if (obj == nullptr || !obj->enabled) return;

    if (obj->GetRenderObject() != nullptr && obj->GetRenderObject()->OkToRender() 
        && camera->GetFrustum().InsideFrustrum(obj->transform.GetPosition(), obj->GetRenderObject()->GetBoundingRadius()))
    {
        objsOut.push_back(obj);
    }

    for (GameObject* o : obj->GetChildren())
    {
        PrepareObjects(camera, o, objsOut);
    }
}
