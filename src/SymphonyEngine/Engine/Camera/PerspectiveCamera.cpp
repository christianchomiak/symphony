#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Symphony
{
    const float PerspectiveCamera::DEFAULT_FOV = 60.0f;

    PerspectiveCamera::PerspectiveCamera(float nearPlane, float farPlane, float fov)
        : Camera(nearPlane, farPlane), fieldOfView(fov)
    {
        RecomputeProjectionMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(float nearPlane, float farPlane, float fov, ViewPort& viewport)
        : Camera(nearPlane, farPlane, viewport), fieldOfView(fov)
    {
        RecomputeProjectionMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(ViewPort& viewport)
        : PerspectiveCamera(DEFAULT_FOV, viewport)
    {
    }

    PerspectiveCamera::PerspectiveCamera(float fov)
        : Camera(), fieldOfView(fov)
    {
        RecomputeProjectionMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(float fov, ViewPort& viewport)
        : Camera(viewport), fieldOfView(fov)
    {
        RecomputeProjectionMatrix();
    }
    
    void PerspectiveCamera::Update()
    {
        Camera::Update();
    }

    void PerspectiveCamera::SetViewPort(ViewPort& newViewPort)
    {
        Camera::SetViewPort(newViewPort);
        RecomputeProjectionMatrix();
    }
    
    //TO-DO: Update the camera when the viewport changes
    void PerspectiveCamera::RecomputeProjectionMatrix()
    {
        float fov = fieldOfView < 0.f ? -fieldOfView : fieldOfView;
        projectionMatrix = glm::perspective(glm::radians(fov), viewport.AspectRatio(), nearPlane, farPlane);
    }
}