#include "SimpleRenderer.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include <functional>

SimpleRenderer::SimpleRenderer()
{
}

SimpleRenderer::~SimpleRenderer()
{
}

void SimpleRenderer::Render(const GameObject* sceneRoot, const std::vector<Camera*>& cameras, const std::vector<Light*>& lights)
{
    std::vector<PossibleObject> objs;
    std::vector<PossibleObject> transparentObjs;
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    //glDepthMask(GL_FALSE); //If false, the depth buffer is read-only
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Camera* cam : cameras)
    {
        PrepareObjects(cam, sceneRoot, objs, transparentObjs);
        std::sort(transparentObjs.begin(), transparentObjs.end(), PossibleObject::ClosestObjectToCamera);
        
        glDisable(GL_BLEND);
        RenderCamera(cam, objs, lights);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
        //glBlendFunc(GL_ONE, GL_ZERO);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        RenderCamera(cam, transparentObjs, lights);

        objs.clear();
        transparentObjs.clear(); 

    }
}

void SimpleRenderer::RenderCamera(Camera* cam, const std::vector<PossibleObject>& objects, const std::vector<Light*>& lights)
{
    glm::mat4 P = cam->ProjectionMatrix(); //glm::mat4(1);
    glm::mat4 V = cam->ViewMatrix();

    GLuint shaderID = 0;
    for (auto go : objects)
    {
        auto rObject = go.obj->GetRenderObject();
        Shader& ss = *(rObject->GetShader());
        ss.Use();

        if (rObject->GetMesh()->AllowFaceCulling())
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }

        /* Update the shader with light data if it uses lights */
        /* Update the shader with light data only if object is within the light's reach (radius) */
        /* Update the shader with light data only if light gameobject is enabled */
        int activeLights = 0;
        for (; activeLights < lights.size(); ++activeLights)
        {
            if (!lights[activeLights]->enabled) continue;
            lights[activeLights]->UpdateShader(rObject->GetShader(), activeLights);
        }
        glUniform1i(glGetUniformLocation(ss.ID(), "numberOfIncomingLights"), activeLights);
        
        if (rObject->GetTexture().ID() > 0)
        {
            //glActiveTexture(GL_TEXTURE0);
            ProcessTexture(rObject->GetTexture());
        }

        glUniform3fv(glGetUniformLocation(ss.ID(), "cameraPosition"), 1, glm::value_ptr(cam->transform.GetPosition()));

        // Set material properties
        glUniform3fv(glGetUniformLocation(ss.ID(), "material.ambient"), 1, glm::value_ptr(rObject->material.ambient));
        glUniform3fv(glGetUniformLocation(ss.ID(), "material.diffuse"), 1, glm::value_ptr(rObject->material.diffuse));
        glUniform3fv(glGetUniformLocation(ss.ID(), "material.specular"), 1, glm::value_ptr(rObject->material.specular));
        glUniform1f(glGetUniformLocation(ss.ID(), "material.shininess"), rObject->material.shininess);
            
        //glUniformMatrix4fv(ss("MVP"), 1, GL_FALSE, glm::value_ptr(P*V*go->transform.GetWorldTransformMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(ss.ID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(go.obj->transform.GetWorldTransformMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(ss.ID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(V));
        glUniformMatrix4fv(glGetUniformLocation(ss.ID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(P));
        
        //These two are only for the Depth Testing shader
        glUniform1f(glGetUniformLocation(ss.ID(), "nearPlane"), cam->GetNearPlane());
        glUniform1f(glGetUniformLocation(ss.ID(), "farPlane"), cam->GetFarPlane());

        rObject->GetMesh()->Render();

        ss.Release();
    }
    //glActiveTexture(0);
}

void SimpleRenderer::PrepareObjects(const Camera* camera, const GameObject* obj,
                                    std::vector<PossibleObject>& opaqueObjectsOut,
                                    std::vector<PossibleObject>& transparentObjectsOut)
{
    if (obj == nullptr || !obj->enabled) return;

    auto rObj = obj->GetRenderObject();
    if (rObj != nullptr && rObj->OkToRender()
        && camera->GetFrustum().InsideFrustrum(obj->transform.GetPosition(), rObj->GetBoundingRadius()))
    {
        if (obj->GetRenderObject()->GetTexture().GetTransparencyType() != Texture::Transparency::SEMI)
        {
            //For now, We can disregard the distance between opaque objects and the camera.
            //Maybe later it could be handy to have that info, though.
            opaqueObjectsOut.push_back(PossibleObject(obj, 0.0f)); // glm::distance2(obj->transform.GetPosition(), camera->transform.GetPosition())));
        }
        else
        {
            transparentObjectsOut.push_back(PossibleObject(obj, glm::distance2(obj->transform.GetPosition(), camera->transform.GetPosition())));
        }
    }

    for (GameObject* o : obj->GetChildren())
    {
        PrepareObjects(camera, o, opaqueObjectsOut, transparentObjectsOut);
    }
}

/*void SimpleRenderer::PrepareObjects(const Camera * camera, const GameObject * obj,
                                    std::vector<const GameObject*>& objsOut, bool filterOpaque)
{
    if (obj == nullptr || !obj->enabled) return;
    
    bool renderingCondition = obj->GetRenderObject() != nullptr
                           && obj->GetRenderObject()->OkToRender()
                           && (
                                    (filterOpaque && !obj->GetRenderObject()->GetTexture().HasTransparency())
                                || (!filterOpaque &&  obj->GetRenderObject()->GetTexture().HasTransparency())
                            )
                           && camera->GetFrustum().InsideFrustrum(obj->transform.GetPosition(),
                                                                  obj->GetRenderObject()->GetBoundingRadius())
                           ;
    
    if (renderingCondition)
    {
        objsOut.push_back(obj);
    }

    for (GameObject* o : obj->GetChildren())
    {
        PrepareObjects(camera, o, objsOut);
    }
}*/
