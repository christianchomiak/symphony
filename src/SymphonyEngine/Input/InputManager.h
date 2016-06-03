#pragma once

#include "../Utilities/Singleton.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Symphony
{
    class InputManager : public Singleton<InputManager>
    {
        friend class Singleton<InputManager>;
    public:
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
            mouse->xPosition = xpos;
            mouse->yPosition = ypos;
        }

        static Keyboard* GetKeyboard() { return Instance()->keyboard; }
        static Mouse* GetMouse() { return Instance()->mouse; }
        static void Update() { Instance()->UpdateInput(); }

        void UpdateInput()
        {
            keyboard->Update();
            mouse->Update();
        }
    protected:
        Keyboard* keyboard;
        Mouse* mouse;
    private:
        InputManager();
        virtual ~InputManager();
    };
}