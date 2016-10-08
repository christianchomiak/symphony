#pragma once

//#include "../Utilities/Singleton.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

#include "../Debugging/Debugging.h"
#include "../Macros/PlatformMacros.h"
#include "../Macros/ClassMacros.h"

namespace Symphony
{
    class InputManager
    {
        SINGLETON(InputManager)
    public:
        //TO-DO: Figure out why there's a linking error when these static functions are defined outside of the class
        //       but within the header file
        
        static void KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Instance()->keyboard->UpdateKey(key, action);
        }

        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            Instance()->mouse->UpdateButton(button, action);
        }

        static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
        {
            Mouse* mouse = Instance()->mouse;
            //mouse->position.x = (float) xpos;
            //mouse->position.y = (float) ypos;
            mouse->UpdatePosition((float)xpos, (float)ypos);
        }

        static void GamePadStatusCallback(int gamepadID, int event);

        static Mouse*    GetMouse()    { return Instance()->mouse;      }
        static Keyboard* GetKeyboard() { return Instance()->keyboard;   }
        static GamePad*  GetGamepad(int index)
        {
            GamePad* gamepad = index > -1 && index < GLFW_JOYSTICK_LAST + 1 ? Instance()->gamepad[index] : nullptr;
            DEBUG_ONLY(if (!gamepad) Debug::LogWarningF("Could not find controller #%d", index));
            return gamepad;
        }
        
        static void Update() { Instance()->UpdateInput(); }

    protected:
        Keyboard* keyboard;
        Mouse* mouse;
        
        //TO-DO: Would it be better if all the gamepad objects were instantiated by default
        GamePad* gamepad[GLFW_JOYSTICK_LAST + 1];
        
        void UpdateInput()
        {
            keyboard->Update();
            mouse->Update();
            
            for (size_t i = 0; i < GLFW_JOYSTICK_LAST + 1; ++i)
            {
                if (gamepad[i] && gamepad[i]->connected)
                {
                    gamepad[i]->Update();
                }
            }
        }

    public: 
    };
}