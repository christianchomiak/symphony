#include "FreeRoamCamera.h"

#include "../SymphonyEngine/Time/Time.h"
#include "../SymphonyEngine/Input/InputManager.h"

FreeRoamCamera::FreeRoamCamera()
    : PerspectiveCamera(60.f)
{
    Mouse* mouse = InputManager::GetMouse();
}

void FreeRoamCamera::Update()
{
    Mouse* mouse = InputManager::GetMouse();

    glm::vec2 mouseOffset = mouse->DeltaPosition();

    yaw -= mouseOffset.x;
    pitch += mouseOffset.y;

    if      (pitch >  89.f) pitch = 89.f;
    else if (pitch < -89.f) pitch = -89.f;

    transform.SetLocalRotation(pitch, yaw, 0.f);

    //transform.Rotate(-mouseOffset.y, mouseOffset.x, 0);
    
    Keyboard* keyboard = InputManager::GetKeyboard();

    float speed = 50.f;

    glm::vec3 dir;
    if (keyboard->KeyPressed(Key::Q))
    {
        dir += glm::vec3(0, 1, 0); // transform.Up();
    }
    else if (keyboard->KeyPressed(Key::E))
    {
        dir -= glm::vec3(0, 1, 0); // transform.Up();
    }

    if (keyboard->KeyPressed(Key::W))
    {
        dir -= transform.Forward();
    }
    else if (keyboard->KeyPressed(Key::S))
    {
        dir += transform.Forward();
    }

    if (keyboard->KeyPressed(Key::A))
    {
        dir-= transform.Right();
    }
    else if (keyboard->KeyPressed(Key::D))
    {
        dir += transform.Right();
    }
    
    if (dir.length() > 0.f)
    {
        dir *= speed * Time::DeltaTime();
        transform.Translate(dir.x, dir.y, dir.z);
    }
    
    PerspectiveCamera::Update();

    if (keyboard->KeyDown(Key::SPACE)) std::cout << transform << std::endl;
}

