#include "Camera.h"

//#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/transform.hpp>

const float Symphony::Camera::DEFAULT_ZNEAR = 0.1f;
const float Symphony::Camera::DEFAULT_ZFAR = 1000.f;

Symphony::Camera::Camera()
    : nearPlane(DEFAULT_ZNEAR), farPlane(DEFAULT_ZFAR)
{
}

Symphony::Camera::Camera(float nearPlane, float farPlane)
    : nearPlane(nearPlane), farPlane(farPlane)
{
}

Symphony::Camera::Camera(float nearPlane, float farPlane, ViewPort& vp)
    : nearPlane(nearPlane), farPlane(farPlane), viewport(vp)
{
}

Symphony::Camera::Camera(ViewPort& vp)
    : nearPlane(DEFAULT_ZNEAR), farPlane(DEFAULT_ZFAR), viewport(vp)
{
}

void Symphony::Camera::SetViewPort(ViewPort& newViewPort)
{
    viewport = newViewPort;
}

const glm::mat4& Symphony::Camera::BuildViewMatrix() const
{
    //TO-DO: create a way for the camera to keep track of an object
    //return glm::lookAt(transform.GetLocalPosition(), transform.GetLocalPosition() + transform.Forward(), transform.Up());

    return glm::toMat4(transform.GetLocalRotation())
         * glm::translate(-transform.GetLocalPosition());
}
