#pragma once

#include <glm/mat4x4.hpp>
#include <Scene/GameObject.h>
#include "ViewPort.h"
#include <Rendering/Textures/Skybox.h>

#include "Frustum.h"

namespace Symphony
{
    class Camera : public GameObject
    {
    public:
        static const float DEFAULT_ZNEAR, DEFAULT_ZFAR;
        
    public:
        virtual ~Camera() {};
        
        virtual void Update() override;
        virtual void SetViewPort(ViewPort& newViewPort);
        const glm::mat4& Camera::ProjectionMatrix() const;
        const glm::mat4& ViewMatrix() const;
        const Frustum& GetFrustum() const;

        float GetNearPlane() const;
        float GetFarPlane() const;

        void SetSkybox(const Skybox& sBox);
        void SetSkybox(unsigned int newSkybox, Shader* skyboxShader);
        void RenderSkybox() const;
        void UpdateShaderWithSkybox(Shader* shader) const;
    protected:
        float nearPlane, farPlane;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        ViewPort viewport;
        Frustum frustum;
        Skybox skybox;

    protected:
        Camera();
        Camera(float nearPlane, float farPlane);
        Camera(float nearPlane, float farPlane, ViewPort& vp);
        Camera(ViewPort& vp);

        const glm::mat4 BuildViewMatrix() const;
        virtual void RecomputeProjectionMatrix() = 0;
    };

    inline const glm::mat4& Camera::ProjectionMatrix() const
    {
        return projectionMatrix;
    }

    inline const Frustum& Camera::GetFrustum() const
    {
        return frustum;
    }

    inline const glm::mat4& Camera::ViewMatrix() const
    {
        return viewMatrix;
    }

    inline float Camera::GetNearPlane() const
    {
        return nearPlane;
    }

    inline float Camera::GetFarPlane() const
    {
        return farPlane;
    }
}