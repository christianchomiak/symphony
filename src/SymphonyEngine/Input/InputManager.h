#pragma once

//#include "../Utilities/Singleton.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "GamePad.h"

#include "../Macros/ClassMacros.h"
#include "../Debugging/Debugging.h"
#include "../Macros/PlatformMacros.h"

#include "../UI/imgui/ImGuiManager.h"

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
        
        inline static void KeyboardKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods)
        {
            Instance()->keyboard.UpdateKey(key, action);
            ImGuiManager::ImGui_ImplGlfwGL3_KeyCallback(key, scancode, action, mods);
            
            //We'd like to render the mouse cursor and interact with imgui
            if (key == Key::CTRL_LEFT && action == GLFW_PRESS)
            {
                Instance()->engineIsBlockingInput = !Instance()->engineIsBlockingInput;
            }
        }

        inline static void MouseButtonCallback(GLFWwindow*, int button, int action, int mods)
        {
            Instance()->mouse.UpdateButton(button, action);
        }

        inline static void MousePositionCallback(GLFWwindow*, double xpos, double ypos)
        {
            //mouse->position.x = (float) xpos;
            //mouse->position.y = (float) ypos;
            Instance()->mouse.UpdatePosition((float) xpos, (float) ypos);
        }

        inline static void ImGui_ImplGlfwGL3_ScrollCallback(GLFWwindow*, double xoffset, double yoffset)
        {
            Instance()->mouse.UpdateScroll(xoffset, yoffset); // Use fractional mouse wheel, 1.0 unit 5 lines.
        }

        inline static void ImGui_ImplGlfwGL3_CharCallback(GLFWwindow*, unsigned int c)
        {
            ImGuiManager::ImGui_ImplGlfwGL3_CharCallback(c);
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

        //In a future, this should block high level input actions, instead of the actual input
        //i.e. it doesn't affect querying if a key is pressed but whether an action mapped to that key is on.
        inline static bool InputIsBlocked()
        {
            return Instance()->engineIsBlockingInput || ImGuiManager::WantsToCaptureKeyboard();
        }

    protected:
        Mouse    mouse;
        Keyboard keyboard;
        bool     engineIsBlockingInput;
        
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