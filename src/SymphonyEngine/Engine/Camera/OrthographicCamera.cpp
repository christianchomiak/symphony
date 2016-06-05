#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Symphony
{
    OrthographicCamera::OrthographicCamera(float nearPlane, float farPlane, float left, float right, float top, float bottom, ViewPort & viewport)
        : Camera(nearPlane, farPlane, viewport), left(left), right(right), top(top), bottom(bottom)
    {
        RecomputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(float nearPlane, float farPlane,
                                           float left, float right, float top, float bottom)
        : Camera(nearPlane, farPlane), left(left), right(right), top(top), bottom(bottom)
    {
        RecomputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom)
        : left(left), right(right), top(top), bottom(bottom)
    {
        RecomputeProjectionMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, ViewPort& viewport)
        : Camera(viewport), left(left), right(right), top(top), bottom(bottom)
    {
    }

    void OrthographicCamera::Update()
    {
        GameObject::Update();
    }

    void OrthographicCamera::SetViewPort(ViewPort& newViewPort)
    {
        Camera::SetViewPort(newViewPort);
    }

    void OrthographicCamera::RecomputeProjectionMatrix()
    {
        projectionMatrix = glm::ortho(left, right, bottom, top);
    }
}
