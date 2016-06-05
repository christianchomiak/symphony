#pragma once

#include "Camera.h"

namespace Symphony
{
    class OrthographicCamera : public Camera
    {
    public:
        static const float DEFAULT_FOV;

    public:
        OrthographicCamera() = delete;
        OrthographicCamera(float nearPlane, float farPlane, float left, float right, float top, float bottom, ViewPort& viewport);
        OrthographicCamera(float nearPlane, float farPlane, float left, float right, float top, float bottom);
        OrthographicCamera(float left, float right, float top, float bottom);
        OrthographicCamera(float left, float right, float top, float bottom, ViewPort& viewport);
        virtual ~OrthographicCamera();

        virtual void Update() override;
        virtual void SetViewPort(ViewPort& newViewPort) override;

    protected:
        float left;
        float right;
        float top;
        float bottom;

    protected:
        virtual void RecomputeProjectionMatrix() override;
    };
}