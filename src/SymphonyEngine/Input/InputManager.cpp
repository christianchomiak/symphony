#include "InputManager.h"

namespace Symphony
{
    InputManager::InputManager()
    {
        keyboard = new Keyboard();
        mouse = new Mouse();

        for (size_t i = 0; i < GLFW_JOYSTICK_LAST + 1; ++i)
        {
            if (glfwJoystickPresent(i))
            {
                Debug::LogF("Connected gamepad #%d (%s)", i, glfwGetJoystickName(i));
            }

            gamepad[i] = glfwJoystickPresent(i) ? new GamePad(i) : nullptr;
        }
    }

    InputManager::~InputManager()
    {
        delete keyboard;
        delete mouse;

        for (size_t i = 0; i < GLFW_JOYSTICK_LAST + 1; ++i)
        {
            delete gamepad[i];
            gamepad[i] = nullptr;
        }
    }
    
    void InputManager::GamePadStatusCallback(int gamepadID, int event)
    {
        if (event == GLFW_CONNECTED)
        {
            if (Instance()->gamepad[gamepadID] == nullptr)
            {
                Instance()->gamepad[gamepadID] = new GamePad(gamepadID);
            }
            
            // The gamepad was connected
            Debug::LogF("Connected gamepad #%d (%s)", gamepadID, glfwGetJoystickName(gamepadID));
        }
        else if (event == GLFW_DISCONNECTED)
        {
            /*delete Instance()->gamepad[gamepadID];
            Instance()->gamepad[gamepadID] = nullptr;*/

            // The gamepad was disconnected
            Debug::LogF("Disconnected gamepad #%d", gamepadID);
        }

        Instance()->gamepad[gamepadID]->connected = event == GLFW_CONNECTED;
    }
}

