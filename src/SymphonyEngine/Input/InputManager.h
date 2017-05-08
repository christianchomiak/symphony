#pragma once

//#include "../Utilities/Singleton.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "GamePad.h"

#include "../Macros/ClassMacros.h"
#include "../Debugging/Debugging.h"
#include "../Macros/PlatformMacros.h"

namespace Symphony
{
    typedef const Mouse&    MouseRef;
    typedef const Keyboard& KeyboardRef;

    class InputManager
    {
        friend class SymphonyEngine;

        SINGLETON(InputManager)

    public:
        //TO-DO: Figure out why there's a linking error when these static functions are defined outside of the class
        //       but within the header file
        
        inline static void KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Instance()->keyboard.UpdateKey(key, action);
        }

        inline static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            Instance()->mouse.UpdateButton(button, action);
        }

        inline static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
        {
            //mouse->position.x = (float) xpos;
            //mouse->position.y = (float) ypos;
            Instance()->mouse.UpdatePosition((float) xpos, (float) ypos);
        }

        static void GamePadStatusCallback(int gamepadID, int event);

        inline static MouseRef    GetMouse()    { return Instance()->mouse;    }
        inline static KeyboardRef GetKeyboard() { return Instance()->keyboard; }
        inline static GamePad*    GetGamepad(int index)
        {
            GamePad* gamepad = (index > -1 && index < GLFW_JOYSTICK_LAST + 1) ? Instance()->gamepad[index] : nullptr;
            DEBUG_ONLY(if (!gamepad) Debug::LogWarningF("Could not find controller #%d", index));
            return gamepad;
        }
        
    protected:
        Mouse    mouse;
        Keyboard keyboard;
        
        //TO-DO: Would it be better if all the gamepad objects were instantiated by default
        GamePad* gamepad[GLFW_JOYSTICK_LAST + 1];

        inline static void Update()
        {
            Instance()->UpdateInput();
        }

        inline void UpdateInput()
        {
            mouse.Update();
            keyboard.Update();
            
            for (size_t i = 0; i < GLFW_JOYSTICK_LAST + 1; ++i)
            {
                if (gamepad[i] && gamepad[i]->connected)
                {
                    gamepad[i]->Update();
                }
            }
        }
    };
}