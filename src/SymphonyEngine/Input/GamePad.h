#pragma once

#include <GLFW/glfw3.h>
#include "Input.h"

namespace Symphony
{
    enum PadButton
    {
        GAMEPAD_A = 0,
        GAMEPAD_B = 1,
        GAMEPAD_X = 2,
        GAMEPAD_Y = 3,

        GAMEPAD_LEFT_SHOULDER = 4,
        GAMEPAD_RIGHT_SHOULDER = 5,

        GAMEPAD_BACK = 6,
        GAMEPAD_START = 7,

        GAMEPAD_LEFT_STICK = 8,
        GAMEPAD_RIGHT_STICK = 9,

        GAMEPAD_DPAD_UP = 10,
        GAMEPAD_DPAD_RIGHT = 11,
        GAMEPAD_DPAD_DOWN = 12,
        GAMEPAD_DPAD_LEFT = 13
    };

    enum PadAxis
    {
        GAMEPAD_LEFT_X = 0,
        GAMEPAD_LEFT_Y = 1,

        GAMEPAD_RIGHT_X = 2,
        GAMEPAD_RIGHT_Y = 3,

        GAMEPAD_LEFT_TRIGGER = 4,
        GAMEPAD_RIGHT_TRIGGER = 5
    };

    class GamePad
    {
        friend class InputManager;
    public:
        bool Connected() const;
        bool AnyButtonPressed() const;

        //TO-DO: Should these be inlined?
        
        bool      ButtonUp(PadButton button)  const;
        bool    ButtonDown(PadButton button)  const;
        bool    ButtonHold(PadButton button)  const;
        bool ButtonPressed(PadButton button)  const;
        
        float GetAxisValue(PadAxis axisNumber) const;

        const char* Name() const;

    protected:
        int gamepadID;
        bool connected;

        bool anyButtonPressed;

        int numberOfButtons;
        InputState* buttons;

        int numberOfAxes;
        const float* axes;

    protected:
        GamePad(int gamepadID = 0);
        ~GamePad();

        void Reset();
        void Update();
    };
    
    inline bool GamePad::Connected() const
    {
        return connected;
    }

    inline bool GamePad::AnyButtonPressed() const
    {
        return anyButtonPressed;
    }
    
    inline const char* GamePad::Name() const
    {
        return connected ? glfwGetJoystickName(gamepadID) : "";
    }
}