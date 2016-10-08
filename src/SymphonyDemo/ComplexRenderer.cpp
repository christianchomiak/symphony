#include "ComplexRenderer.h"

#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>    // std::sort
#include <vector>       // std::vector

ComplexRenderer::ComplexRenderer()
{
    bool useRBO = true;

    screenQuad = Mesh::Quad();
    screenShader = Shader::GetShader("SIMPLE");

    //TO-DO: These textures should be updated whenever the screen's width & height change. Just saying...
    glGenTextures(1, &bufferColourTexture);
    glBindTexture(GL_TEXTURE_2D, bufferColourTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen::Width(), Screen::Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    

    if (useRBO)
    {
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Screen::Width(), Screen::Height());
    }
    else
    {
        glGenTextures(1, &bufferDepthTexture);
        glBindTexture(GL_TEXTURE_2D, bufferDepthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Screen::Width(), Screen::Height(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    
    glGenFramebuffers(1, &frameBuffer); //We'll render the scene into this
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferColourTexture, 0);


    if (useRBO)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    }
    else
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, bufferDepthTexture, 0);
    }
        
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) // || !bufferDepthTexture || !bufferColourTexture)
    {
        std::cerr << "Problem in ComplexRenderer" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    if (useRBO) glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

ComplexRenderer::~ComplexRenderer()
{
    delete screenQuad;
    //delete screenShader;

    glDeleteTextures(1, &bufferDepthTexture);
    glDeleteTextures(1, &bufferColourTexture);

    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteRenderbuffers(1, &rbo);
}

void ComplexRenderer::Render(const Scene* scene)
{
    // First pass
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glEnable(GL_DEPTH_TEST);

    std::vector<OrderableObject> objs;
    std::vector<OrderableObject> transparentObjs;

    for (Camera* cam : scene->Cameras())
    {
        PrepareObjects(cam, scene->GetSceneRoot(), objs, transparentObjs);

        //We want to draw first the farthest objects, so we order the list from
        //farthest to closest and trasverse it normally instead of doing it the
        //other way around and trasversing it in reverse order.
        std::sort(transparentObjs.begin(), transparentObjs.end(), OrderableObject::FarthestObjectFromCamera);

        glDisable(GL_BLEND);
        RenderCamera(cam, objs, scene->Lights());

        cam->RenderSkybox();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
        //glBlendFunc(GL_ONE, GL_ZERO);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        RenderCamera(cam, transparentObjs, scene->Lights());

        objs.clear();
        transparentObjs.clear();
    }

    // Second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    screenShader->Use();
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, bufferColourTexture);
        screenQuad->Render();
    glUseProgram(0);
}

void ComplexRenderer::RenderCamera(Camera* cam, const std::vector<OrderableObject>& objects, const std::vector<Light*>& lights)
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

        cam->UpdateShaderWithSkybox(rObject->GetShader());
        glUniform3fv(glGetUniformLocation(ss.ID(), "cameraPosition"), 1, glm::value_ptr(cam->transform.GetPosition()));

        /* Update the shader with light data if it uses lights */
        /* Update the shader with light data only if object is within the light's reach (radius) */
        /* Update the shader with light data only if light gameobject is enabled */
        size_t activeLights = 0;
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

void ComplexRenderer::PrepareObjects(const Camera* camera, const GameObject* obj,
    std::vector<OrderableObject>& opaqueObjectsOut,
    std::vector<OrderableObject>& transparentObjectsOut)
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
            opaqueObjectsOut.push_back(OrderableObject(obj, 0.0f)); // glm::distance2(obj->transform.GetPosition(), camera->transform.GetPosition())));
        }
        else
        {
            transparentObjectsOut.push_back(OrderableObject(obj, glm::distance2(obj->transform.GetPosition(), camera->transform.GetPosition())));
        }
    }

    for (GameObject* o : obj->GetChildren())
    {
        PrepareObjects(camera, o, opaqueObjectsOut, transparentObjectsOut);
    }
}

/*void ComplexRenderer::PrepareObjects(const Camera * camera, const GameObject * obj,
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
