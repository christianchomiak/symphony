#include "Camera.h"

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