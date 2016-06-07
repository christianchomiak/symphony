#include "FreeRoamCamera.h"

#include "../SymphonyEngine/Time/Time.h"
#include "../SymphonyEngine/Input/InputManager.h"

FreeRoamCamera::FreeRoamCamera()
    : PerspectiveCamera(60.f)
{
}

void FreeRoamCamera::Update()
{
    PerspectiveCamera::Update();
    Keyboard* keyboard = InputManager::GetKeyboard();

    float speed = 50.f;

    glm::vec3 dir;
    if (keyboard->KeyPressed(Key::KEY_Q))
    {
        dir += transform.Up();
    }
    else if (keyboard->KeyPressed(Key::KEY_E))
    {
        dir += -transform.Up();
    }

    if (keyboard->KeyPressed(Key::KEY_W))
    {
        dir -= transform.Forward();
    }
    else if (keyboard->KeyPressed(Key::KEY_S))
    {
        dir += transform.Forward();
    }

    if (keyboard->KeyPressed(Key::KEY_A))
    {
        dir-= transform.Right();
    }
    else if (keyboard->KeyPressed(Key::KEY_D))
    {
        dir += transform.Right();
    }

    float deltaTime = Time::DeltaTime();
    if (dir.length() > 0.f)
    {
        dir *= speed;
        transform.Translate(dir.x * deltaTime, dir.y * deltaTime, dir.z * deltaTime);
    }

    float rotationSpeed = 60.f;
    if (keyboard->KeyPressed(Key::ARROW_LEFT))
    {
        transform.Rotate(0, -rotationSpeed * deltaTime, 0);
    }
    else if (keyboard->KeyPressed(Key::ARROW_RIGHT))
    {
        transform.Rotate(0, rotationSpeed * deltaTime, 0);
    }
    
    if (keyboard->KeyPressed(Key::ENTER))
    std::cout << transform << std::endl;
}

