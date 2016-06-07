#include "Mouse.h"

#include <cstring>
#include <iostream>

Symphony::Mouse::Mouse()
{
    anyButtonPressed = false;
    numberOfButtons = GLFW_MOUSE_BUTTON_LAST + 1;
    buttons = new InputState[numberOfButtons];
    Reset();
}

Symphony::Mouse::~Mouse()
{
    delete[] buttons;
}

void Symphony::Mouse::Reset()
{
    std::memset(buttons, InputState::IDLE, numberOfButtons);
}

void Symphony::Mouse::Update()
{
    anyButtonPressed = false;
    
    for (size_t i = 0; i < (size_t)numberOfButtons; ++i)
    {
        if (buttons[i] == InputState::DOWN)
        {
            buttons[i] = InputState::HOLD;
            anyButtonPressed = true;
        }
        else if (buttons[i] == InputState::HOLD)
        {
            anyButtonPressed = true;
        }
        else if (buttons[i] == InputState::UP)
        {
            buttons[i] = InputState::IDLE;
        }

        deltaPosition.x = 0;
        deltaPosition.y = 0;
    }
}

void Symphony::Mouse::UpdateButton(int id, int state)
{
    if (!CheckButtonID(id))
    {
        std::cerr << "Trying to update unknow button" << std::endl;
        return;
    }
    
    if (state == GLFW_PRESS)
    {
        buttons[id] = InputState::DOWN;
    }
    else if (state == GLFW_RELEASE)
    {
        buttons[id] = InputState::UP;
    }
}

void Symphony::Mouse::UpdatePosition(float newX, float newY)
{
    glm::vec2 newPosition = glm::vec2(newX, newY);
    deltaPosition.x = newPosition.x - position.x;
    deltaPosition.y = position.y - newPosition.y;
    position.x = newX;
    position.y = newY;
}

bool Symphony::Mouse::ButtonPressed(int button) const
{
    if (!CheckButtonID(button))
    {
        std::cerr << "Trying to query unknow button" << std::endl;
        return false;
    }
    return buttons[button] == InputState::HOLD || buttons[button] == InputState::DOWN;
}

bool Symphony::Mouse::ButtonUp(int button) const
{
    if (!CheckButtonID(button))
    {
        std::cerr << "Trying to query unknow button" << std::endl;
        return false;
    }
    return buttons[button] == InputState::UP;
}

bool Symphony::Mouse::ButtonDown(int button) const
{
    if (!CheckButtonID(button))
    {
        std::cerr << "Trying to query unknow button" << std::endl;
        return false;
    }
    return buttons[button] == InputState::DOWN;
}

bool Symphony::Mouse::ButtonHold(int button) const
{
    if (!CheckButtonID(button))
    {
        std::cerr << "Trying to query unknow button" << std::endl;
        return false;
    }
    return buttons[button] == InputState::HOLD;
}