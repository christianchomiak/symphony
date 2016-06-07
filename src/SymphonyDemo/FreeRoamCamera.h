#pragma once

#include "../SymphonyEngine/Engine/Camera/PerspectiveCamera.h"

using namespace Symphony;

class FreeRoamCamera : public PerspectiveCamera
{
public:
    FreeRoamCamera();
    virtual ~FreeRoamCamera() {}

    virtual void Update() override;
};