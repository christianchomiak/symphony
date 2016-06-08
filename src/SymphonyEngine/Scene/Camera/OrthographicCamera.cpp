#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Symphony
{
    OrthographicCamera::OrthographicCamera(float nearPlane, float farPlane, float left, float right, float top, float bottom, ViewPort & viewport)
        : Camera(nearPlane, farPlane, viewport), left(left), right(right), top(top), bottom(bottom)
    {
        name = "Ortho Camera";
        RecomputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(float nearPlane, float farPlane,
                                           float left, float right, float top, float bottom)
        : Camera(nearPlane, farPlane), left(left), right(right), top(top), bottom(bottom)
    {
        name = "Ortho Camera";
        RecomputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
        : left(left), right(right), top(top), bottom(bottom)
    {
        name = "Ortho Camera";
        RecomputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, ViewPort& viewport)
        : Camera(viewport), left(left), right(right), top(top), bottom(bottom)
    {
        name = "Ortho Camera";
    }

    void OrthographicCamera::Update()
    {
        Camera::Update();
    }
    
    void OrthographicCamera::SetViewPort(ViewPort& newViewPort)
    {
        Camera::SetViewPort(newViewPort);
    }

    //TO-DO: The Ortho camera isn't working correctly, nothing appears on-screen
    void OrthographicCamera::RecomputeProjectionMatrix()
    {
        projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    }
}