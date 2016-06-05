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
        virtual ~Camera();
        
        virtual void Update() override = 0;
        const glm::mat4& Camera::ProjectionMatrix() const;

        virtual void SetViewPort(ViewPort& newViewPort);
        
    protected:
        float nearPlane, farPlane;
        glm::mat4 projectionMatrix;
        ViewPort viewport;

    protected:
        Camera();
        Camera(float nearPlane, float farPlane);
        Camera(float nearPlane, float farPlane, ViewPort& vp);
        Camera(ViewPort& vp);
        virtual void RecomputeProjectionMatrix() = 0;
    };
    
    inline const glm::mat4& Camera::ProjectionMatrix() const
    {
        return projectionMatrix;
    }
}