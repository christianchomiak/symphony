#include "InputManager.h"

Symphony::InputManager::InputManager()
{
    keyboard = new Keyboard();
    mouse = new Mouse();
}

Symphony::InputManager::~InputManager()
{
    delete keyboard;
    delete mouse;
}
