#include "InputManager.h"

Symphony::InputManager::InputManager()
{
    keyboard = new Keyboard();
}

Symphony::InputManager::~InputManager()
{
    delete keyboard;
}
