#include "Keyboard.h"

#include <cstring>
#include <iostream>

Symphony::Keyboard::Keyboard()
{
    numberOfKeys = GLFW_KEY_LAST + 1;
    keys = new InputState[numberOfKeys];
    Reset();
}

Symphony::Keyboard::~Keyboard()
{
    delete[] keys;
}

bool Symphony::Keyboard::KeyPressed(int key) const
{
    if (!CheckKeyID(key))
    {
        std::cerr << "Trying to query unknow key" << std::endl;
        return false;
    }
    return keys[key] == InputState::HOLD || keys[key] == InputState::DOWN;
}

bool Symphony::Keyboard::KeyUp(int key) const
{
    if (!CheckKeyID(key))
    {
        std::cerr << "Trying to query unknow key" << std::endl;
        return false;
    }
    return keys[key] == InputState::UP;
}

bool Symphony::Keyboard::KeyDown(int key) const
{
    if (!CheckKeyID(key))
    {
        std::cerr << "Trying to query unknow key" << std::endl;
        return false;
    }
    return keys[key] == InputState::DOWN;
}

bool Symphony::Keyboard::KeyHold(int key) const
{
    if (!CheckKeyID(key))
    {
        std::cerr << "Trying to query unknow key" << std::endl;
        return false;
    }
    return keys[key] == InputState::HOLD;
}

int Symphony::Keyboard::KeyStatus(int key) const
{
    if (!CheckKeyID(key))
    {
        std::cerr << "Trying to update unknow key" << std::endl;
        return -23;
    }

    return keys[key];
}

void Symphony::Keyboard::Update()
{
    anyKeyPressed = false;
    for (size_t i = 0; i < (size_t)numberOfKeys; ++i)
    {
        if (keys[i] == InputState::DOWN)
        {
            keys[i] = InputState::HOLD;
            anyKeyPressed = true;
        }
        else if (keys[i] == InputState::HOLD)
        {
            anyKeyPressed = true;
        }
        else if (keys[i] == InputState::UP)
        {
            keys[i] = InputState::IDLE;
        }
    }
}

void Symphony::Keyboard::UpdateKey(int id, int state)
{
    if (!CheckKeyID(id))
    {
        std::cerr << "Trying to update unknow key" << std::endl;
        return;
    }
    
    if (state == GLFW_PRESS)
    {
        keys[id] = InputState::DOWN;
    }
    else if (state == GLFW_RELEASE)
    {
        keys[id] = InputState::UP;
    }
}

void Symphony::Keyboard::Reset()
{
    /*for (size_t i = 0; i < numberOfKeys; ++i)
    {
        keys[i] = KeyState::IDLE;
    }*/
    std::memset(keys, InputState::IDLE, numberOfKeys);
}
