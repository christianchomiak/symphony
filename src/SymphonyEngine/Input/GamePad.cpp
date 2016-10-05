#include "GamePad.h"

#include <cstring>
#include "../Debugging/Debugging.h"

namespace Symphony
{
    GamePad::GamePad(int gamepadID)
        : gamepadID(gamepadID), anyButtonPressed(false), connected(true)
    {
        //TO-DO: Is the memory address of this array constant throughout the execution of the program?
        const unsigned char* gpButtons = glfwGetJoystickButtons(gamepadID, &numberOfButtons);
        buttons = new InputState[numberOfButtons];
        
        axes = glfwGetJoystickAxes(gamepadID, &numberOfAxes);

        Reset();
    }
    
    GamePad::~GamePad()
    {
        delete[] buttons;
    }
    
    bool GamePad::ButtonUp(PadButton button) const
    {
        return connected
            && (button > -1 && button < numberOfButtons)
            && buttons[button] == InputState::UP;
    }

    bool GamePad::ButtonDown(PadButton button) const
    {
        return connected
            && (button > -1 && button < numberOfButtons)
            && buttons[button] == InputState::DOWN;
    }

    bool GamePad::ButtonHold(PadButton button) const
    {
        return connected
            && (button > -1 && button < numberOfButtons)
            && buttons[button] == InputState::HOLD;
    }

    bool GamePad::ButtonPressed(PadButton button) const
    {
        return connected 
            && (button > -1 && button < numberOfButtons)
            && (buttons[button] == InputState::HOLD || buttons[button] == InputState::DOWN);
    }
    
    float GamePad::GetAxisValue(PadAxis axisNumber) const
    {
        return connected && (axisNumber > -1 && axisNumber < numberOfAxes) && axes
               ?
               axes[axisNumber] : 0.0f;
    }

    void GamePad::Reset()
    {
        for (size_t i = 0; i < (size_t)numberOfButtons; ++i)
        {
            buttons[i] = InputState::IDLE;
        }
        //TO-DO: Why is this memset not working???
        //std::memset(buttons, InputState::IDLE, numberOfButtons);
    }
    
    void GamePad::Update()
    {
        anyButtonPressed = false;
        
        connected = glfwJoystickPresent(gamepadID) == GLFW_TRUE;
        if (!connected)
        {
            return;
        }
        
        axes = glfwGetJoystickAxes(gamepadID, &numberOfAxes);

        const unsigned char* gpButtons = glfwGetJoystickButtons(gamepadID, &numberOfButtons);
        
        if (numberOfButtons != 0 && gpButtons != nullptr)
        {
            for (size_t i = 0; i < (size_t)numberOfButtons; ++i)
            {
                auto currButtonState = gpButtons[i];
                
                switch (buttons[i])
                {
                case InputState::IDLE:
                    if (currButtonState == GLFW_PRESS) buttons[i] = InputState::DOWN;
                    break;
                case InputState::DOWN:
                    if (currButtonState == GLFW_PRESS) buttons[i] = InputState::HOLD;
                    else if (currButtonState == GLFW_RELEASE) buttons[i] = InputState::UP;
                    break;
                case InputState::UP:
                    if (currButtonState == GLFW_PRESS) buttons[i] = InputState::DOWN;
                    else if (currButtonState == GLFW_RELEASE) buttons[i] = InputState::IDLE;
                    break;
                case InputState::HOLD:
                    if (currButtonState == GLFW_RELEASE) buttons[i] = InputState::UP;
                    break;
                default:
                    Debug::LogWarning("I shouldn't be here");
                    break;
                }

                anyButtonPressed |= buttons[i] == InputState::DOWN || buttons[i] == InputState::HOLD;
            }
        }
        else
        {
            Debug::LogErrorF("Trying to update gamepad #%d but no buttons were found");
        }
    }
}