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
    mouseOffset *= sensitivity;
    
    if (glm::abs(mouseOffset.x) < 0.25f)
    {
        mouseOffset.x = 0.f;
    }
    if (glm::abs(mouseOffset.y) < 0.25f)
    {
        mouseOffset.y = 0.f;
    }

    if (true)
    {
        yaw -= mouseOffset.x;
        pitch += mouseOffset.y;
        if (pitch > 89.f) pitch = 89.f;
        else if (pitch < -89.f) pitch = -89.f;
        transform.SetLocalRotation(pitch, yaw, 0.f);
    }
    else
    {
        transform.Rotate(-mouseOffset.y, mouseOffset.x, 0);
    }


    /*float mouseXOffset = mouse->PositionX() - mouseXLast;
    float mouseYOffset = mouseYLast - mouse->PositionY();

    mouseXLast = mouse->PositionX();
    mouseYLast = mouse->PositionY();

    mouseXOffset *= sensitivity;
    mouseYOffset *= sensitivity;
    
    yaw += mouseXOffset;
    pitch += mouseYOffset;

    std::cout << "Yaw: " << yaw << ", Pitch: " << pitch << std::endl;

    if (pitch > 89.f) pitch = 89.f;
    else if (pitch < -89.f) pitch = -89.f;
    //transform.SetLocalRotation(pitch, yaw, 0.f);
    */


    Keyboard* keyboard = InputManager::GetKeyboard();

    float speed = 50.f;

    glm::vec3 dir;
    if (keyboard->KeyPressed(Key::KEY_Q))
    {
        dir += glm::vec3(0, 1, 0); // transform.Up();
    }
    else if (keyboard->KeyPressed(Key::KEY_E))
    {
        dir -= glm::vec3(0, 1, 0); // transform.Up();
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
    
    PerspectiveCamera::Update();

    if (keyboard->KeyDown(Key::SPACE))
    std::cout << transform << std::endl;
}

