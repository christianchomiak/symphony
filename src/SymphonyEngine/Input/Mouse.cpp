#include "Mouse.h"

#include <cstring>
#include <iostream>

#include "../Debugging/Debugging.h"

namespace Symphony
{
    Mouse::Mouse()
        : anyButtonPressed(false), sensitivity(0.05f),
          numberOfButtons(GLFW_MOUSE_BUTTON_LAST + 1)
    {
        buttons = new InputState[numberOfButtons];
        Reset();
    }

    Mouse::~Mouse()
    {
        delete[] buttons;
    }

    void Mouse::Reset()
    {
        std::memset(buttons, InputState::IDLE, numberOfButtons);
    }

    void Mouse::Update()
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

    void Mouse::UpdateButton(int id, int state)
    {
        if (!CheckButtonID(id))
        {
            Debug::LogErrorF("Trying to update unknow mouse button (%d)", id);
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

    void Mouse::UpdatePosition(float newX, float newY)
    {
        glm::vec2 newPosition = glm::vec2(newX, newY);
        deltaPosition.x = newPosition.x - position.x;
        deltaPosition.y = position.y - newPosition.y;
        position.x = newX;
        position.y = newY;
        deltaPosition *= sensitivity;
    }

    bool Mouse::ButtonPressed(int button) const
    {
        if (!CheckButtonID(button))
        {
            Debug::LogErrorF("Trying to query unknow mouse button (%d)", button);
            return false;
        }
        return buttons[button] == InputState::HOLD || buttons[button] == InputState::DOWN;
    }

    bool Mouse::ButtonUp(int button) const
    {
        if (!CheckButtonID(button))
        {
            Debug::LogErrorF("Trying to query unknow mouse button (%d)", button);
            return false;
        }
        return buttons[button] == InputState::UP;
    }

    bool Mouse::ButtonDown(int button) const
    {
        if (!CheckButtonID(button))
        {
            Debug::LogErrorF("Trying to query unknow mouse button (%d)", button);
            return false;
        }
        return buttons[button] == InputState::DOWN;
    }

    bool Mouse::ButtonHold(int button) const
    {
        if (!CheckButtonID(button))
        {
            Debug::LogErrorF("Trying to query unknow mouse button (%d)", button);
            return false;
        }
        return buttons[button] == InputState::HOLD;
    }


    void Mouse::SetSensitivity(float newSensitivity)
    {
        if (newSensitivity >= 0.0f)
        {
            sensitivity = newSensitivity;
        }
        else
        {
            Debug::LogWarningF("Trying to set a negative sensitivity of %.3f to the mouse. Current value not overwritten.", newSensitivity);
        }
    }
}