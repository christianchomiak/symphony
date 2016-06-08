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

void SimpleRenderer::Render(const GameObject* sceneRoot, const std::vector<Camera*>& cameras, const std::vector<Light*>& lights)
{
    std::vector<const GameObject*> objs;
    
    for (Camera* cam : cameras)
    {
        PrepareObjects(cam, sceneRoot, objs);
        //std::cout << "Rendering " << objs.size() << " object(s)" << std::endl;
        
        RenderCamera(cam, objs, lights);

        objs.clear();
    }
}

void SimpleRenderer::RenderCamera(Camera* cam, const std::vector<const GameObject*>& objects, const std::vector<Light*>& lights)
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

        /* Update the shader with light data if it uses lights */
        /* Update the shader with light data only if object is within the light's reach (radius) */
        /* Update the shader with light data only if light gameobject is enabled */
        for (size_t i = 0; i < lights.size(); ++i)
        {
            if (!lights[i]->enabled) continue;
            lights[i]->UpdateShader(rObject->GetShader());
        }

        if (rObject->GetTexture().id > 0)
        {
            glActiveTexture(GL_TEXTURE0);
            ProcessTexture(rObject->GetTexture());
        }

        glUniform3fv(glGetUniformLocation(ss.ID(), "cameraPosition"), 1, glm::value_ptr(cam->transform.GetPosition()));

        // Set material properties
        glUniform3fv(glGetUniformLocation(ss.ID(), "material.ambient"), 1, glm::value_ptr(rObject->material.ambient));
        glUniform3fv(glGetUniformLocation(ss.ID(), "material.diffuse"), 1, glm::value_ptr(rObject->material.diffuse));
        glUniform3fv(glGetUniformLocation(ss.ID(), "material.specular"), 1, glm::value_ptr(rObject->material.specular));
        glUniform1f(glGetUniformLocation(ss.ID(), "material.shininess"), rObject->material.shininess);
        
        //glUniformMatrix4fv(ss("MVP"), 1, GL_FALSE, glm::value_ptr(P*V*go->transform.GetWorldTransformMatrix()));
        glUniformMatrix4fv(ss("modelMatrix"), 1, GL_FALSE, glm::value_ptr(go->transform.GetWorldTransformMatrix()));
        glUniformMatrix4fv(ss("viewMatrix"), 1, GL_FALSE, glm::value_ptr(V));
        glUniformMatrix4fv(ss("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(P));
        
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
