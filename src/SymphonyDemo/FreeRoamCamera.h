#pragma once

#include "../SymphonyEngine/Scene/Camera/PerspectiveCamera.h"

using namespace Symphony;

class FreeRoamCamera : public PerspectiveCamera
{
public:
    FreeRoamCamera();
    virtual ~FreeRoamCamera() {}

    virtual void Update() override;
protected:
    float pitch = 0.f;
    float yaw = 0.f;
};