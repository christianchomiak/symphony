#include "Camera.h"

//#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Rendering/Mesh/MeshHelper.h"

namespace Symphony
{

    const float Camera::DEFAULT_ZNEAR = 0.1f;
    const float Camera::DEFAULT_ZFAR = 1000.f;

    Camera::Camera()
        : nearPlane(DEFAULT_ZNEAR), farPlane(DEFAULT_ZFAR)
    {
    }

    Camera::Camera(float nearPlane, float farPlane)
        : nearPlane(nearPlane), farPlane(farPlane)
    {
    }

    Camera::Camera(float nearPlane, float farPlane, ViewPort& vp)
        : nearPlane(nearPlane), farPlane(farPlane), viewport(vp)
    {
    }

    Camera::Camera(ViewPort& vp)
        : nearPlane(DEFAULT_ZNEAR), farPlane(DEFAULT_ZFAR), viewport(vp)
    {
    }

    void Camera::SetViewPort(ViewPort& newViewPort)
    {
        viewport = newViewPort;
    }

    const glm::mat4 Camera::BuildViewMatrix() const
    {
        //TO-DO: create a way for the camera to keep track of an object

        //TO-DO: This is not working properly when the camera's rotation is affected
        //       by another, because Forward() and Up() use its local rotation instead of the globl
        return glm::lookAt(transform.GetPosition(), transform.GetPosition() - transform.Forward(), transform.Up());

        /*return glm::toMat4(transform.GetLocalRotation())
             * glm::translate(-transform.GetPosition());*/
    }

    void Camera::Update()
    {
        GameObject::Update();

        //TO-DO: Find a way to cache this, there's no point in computing it
        //       over and over again for objects that don't move or rotate that often.
        viewMatrix = BuildViewMatrix();

        frustum.FromMatrix(projectionMatrix * viewMatrix);
    }

    void Camera::SetSkybox(const Skybox& sBox)
    {
        skybox.skyboxID = sBox.skyboxID;
        skybox.shader = sBox.shader;
        skybox.mesh = sBox.mesh;

        if (!skybox.mesh) skybox.mesh = MeshHelper::CreateCube();
    }

    void Camera::SetSkybox(unsigned int newSkybox, Shader* skyboxShader)
    {
        skybox.skyboxID = newSkybox;
        skybox.shader = skyboxShader;

        if (!skybox.mesh) skybox.mesh = MeshHelper::CreateCube();
    }

    void Camera::RenderSkybox() const
    {
        if (!skybox.IsValidSkybox()) return;

        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

        glDepthMask(GL_FALSE);

        Shader* shader = skybox.shader; // std::get<2>(this->skybox);
                                        //Load the skybox shader
        shader->Use();
        
        glUniformMatrix4fv(glGetUniformLocation(shader->ID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(viewMatrix))));
        glUniformMatrix4fv(glGetUniformLocation(shader->ID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(shader->ID(), "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.skyboxID);

        //Draw the skybox mesh
        skybox.mesh->Render();

        //Unbind the skybox's shader
        glUseProgram(0);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS); // Set depth function back to default
    }

    void Camera::UpdateShaderWithSkybox(Shader* shader) const
    {
        if (shader && skybox.IsValidSkybox())
        {
            auto location = glGetUniformLocation(shader->ID(), "environmentTexture");
            
            if (location >= 0)
            {
                //TO-DO: Standardise the locations of textures that will be used in a shader
                //       For example, all environment textures could be on location #2
                glUniform1i(location, 2);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.skyboxID);
            }
        }
    }
}