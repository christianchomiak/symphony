#pragma once

#include "Camera.h"

namespace Symphony
{
    class PerspectiveCamera: public Camera
    {
    public:
        static const float DEFAULT_FOV;

    public:
        PerspectiveCamera() = delete;
        PerspectiveCamera(float nearPlane, float farPlane, float fov);
        PerspectiveCamera(float nearPlane, float farPlane, float fov, ViewPort& viewport);
        PerspectiveCamera(ViewPort& viewport);
        PerspectiveCamera(float fov);
        PerspectiveCamera(float fov, ViewPort& viewport);

        virtual ~PerspectiveCamera() {};
        
        virtual void Update() override;
        virtual void SetViewPort(ViewPort& newViewPort) override;

    protected:
        float fieldOfView; ///<summary>The fieldOfView factor.</summary>

        //TO-DO: Is the aspect ratio necessary of should it be taken from the viewport?
        //float aspectRatio; ///<summary>The aspectRatio factor.</summary>

    protected:
        virtual void RecomputeProjectionMatrix() override;
    };
}