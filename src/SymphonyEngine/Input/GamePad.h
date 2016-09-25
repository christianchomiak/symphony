#pragma once

#include <GLFW/glfw3.h>
#include "Input.h"

namespace Symphony
{
    class GamePad
    {
        friend class InputManager;
    public:
        bool Connected() const;
        bool AnyButtonPressed() const;

        //TO-DO: Should these be inlined?
        
        bool      ButtonUp(int button)  const;
        bool    ButtonDown(int button)  const;
        bool    ButtonHold(int button)  const;
        bool ButtonPressed(int button)  const;
        
        float GetAxisValue(int axisNumber) const;

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
    
    namespace GButton
    {
        const int GAMEPAD_A = 0;
        const int GAMEPAD_B = 1;
        const int GAMEPAD_X = 2;
        const int GAMEPAD_Y = 3;

        const int GAMEPAD_LEFT_SHOULDER = 4;
        const int GAMEPAD_RIGHT_SHOULDER = 5;

        const int GAMEPAD_BACK = 6;
        const int GAMEPAD_START = 7;

        const int GAMEPAD_LEFT_STICK = 8;
        const int GAMEPAD_RIGHT_STICK = 9;

        const int GAMEPAD_DPAD_UP = 10;
        const int GAMEPAD_DPAD_RIGHT = 11;
        const int GAMEPAD_DPAD_DOWN = 12;
        const int GAMEPAD_DPAD_LEFT = 13;
    }

    namespace Axis
    {
        const int GAMEPAD_LEFT_X        = 0;
        const int GAMEPAD_LEFT_Y        = 1;

        const int GAMEPAD_RIGHT_X       = 2;
        const int GAMEPAD_RIGHT_Y       = 3;

        const int GAMEPAD_LEFT_TRIGGER  = 4;
        const int GAMEPAD_RIGHT_TRIGGER = 5;
    }
}