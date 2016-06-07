#pragma once

#include <glm/mat4x4.hpp>
#include "../GameObject.h"
#include "ViewPort.h"

namespace Symphony
{
    class Camera : public GameObject
    {
    public:
        static const float DEFAULT_ZNEAR, DEFAULT_ZFAR;
        
    public:
        virtual ~Camera() {};
        
        virtual void Update() override;
        const glm::mat4& Camera::ProjectionMatrix() const;

        virtual void SetViewPort(ViewPort& newViewPort);
        const glm::mat4& BuildViewMatrix() const;
        
    protected:
        float nearPlane, farPlane;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        ViewPort viewport;

    protected:
        Camera();
        Camera(float nearPlane, float farPlane);
        Camera(float nearPlane, float farPlane, ViewPort& vp);
        Camera(ViewPort& vp);

        virtual void RecomputeProjectionMatrix() = 0;
    };
    
    inline void Camera::Update()
    {
        GameObject::Update();

        //TO-DO: Find a way to cache this, there's no point in computing it
        //       over and over again for objects that don't move or rotate that often.
        viewMatrix = BuildViewMatrix();
    }

    inline const glm::mat4& Camera::ProjectionMatrix() const
    {
        return projectionMatrix;
    }
}