#include "Mouse.h"

#include <cstring>
#include <iostream>

Symphony::Mouse::Mouse()
{
    anyButtonPressed = false;
    xPosition = 0.0;
    yPosition = 0.0;
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