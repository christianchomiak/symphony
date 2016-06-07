#pragma once

#include "../SymphonyEngine/Engine/Camera/PerspectiveCamera.h"

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