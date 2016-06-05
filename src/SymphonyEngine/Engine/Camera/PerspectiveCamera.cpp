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

    PerspectiveCamera::PerspectiveCamera(float fov, ViewPort& viewport)
        : Camera(viewport), fieldOfView(fov)
    {
        RecomputeProjectionMatrix();
    }

    
    void PerspectiveCamera::Update()
    {
        GameObject::Update();
    }

    void PerspectiveCamera::SetViewPort(ViewPort& newViewPort)
    {
        Camera::SetViewPort(newViewPort);
        RecomputeProjectionMatrix();
    }
    
    void PerspectiveCamera::RecomputeProjectionMatrix()
    {
        projectionMatrix = glm::perspective(fieldOfView, viewport.AspectRatio(), nearPlane, farPlane);
    }
}