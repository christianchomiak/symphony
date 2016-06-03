#pragma once

#include "../Utilities/Singleton.h"
#include "Keyboard.h"

namespace Symphony
{
    class InputManager : public Singleton<InputManager>
    {
        friend class Singleton<InputManager>;
    public:
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            //if (key == GLFW_KEY_E && action == GLFW_PRESS)
            Instance()->keyboard->UpdateKey(key, action);
        }

        Keyboard* GetKeyboard() { return keyboard; }
    protected:
        Keyboard* keyboard;
    private:
        InputManager();
        virtual ~InputManager();
    };
}