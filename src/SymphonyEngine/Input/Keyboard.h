#pragma once

#include <GLFW/glfw3.h>
#include "Input.h"

namespace Symphony
{
    class Keyboard
    {
        friend class InputManager;
    public:
        Keyboard();
        ~Keyboard();

        inline bool AnyKeyPressed() const { return anyKeyPressed; }

        bool KeyPressed(int key) const;
        bool KeyUp(int key)    const;
        bool KeyDown(int key)  const;
        bool KeyHold(int key)  const;
        int KeyStatus(int key) const;
        
        inline bool CheckKeyID(int id) const 
        {
            return (id >= 0 && id < numberOfKeys);
        }

    protected:
        bool anyKeyPressed = false;
        int numberOfKeys;
        InputState* keys;

        void Update();
        void UpdateKey(int id, int state);
        void Reset();
        
    public:

    };

    namespace Key
    {
        const int KEY_UNKOWN = GLFW_KEY_UNKNOWN;

        const int SEMICOLON = GLFW_KEY_SEMICOLON;
        const int APOSTROPHE = GLFW_KEY_APOSTROPHE;
        const int COMMA = GLFW_KEY_COMMA;
        const int PERIOD = GLFW_KEY_PERIOD;
        const int MINUS = GLFW_KEY_MINUS;
        const int SLASH = GLFW_KEY_SLASH;
        const int EQUAL = GLFW_KEY_EQUAL;

        const int LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET;
        const int RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET;
        const int BACKSLASH = GLFW_KEY_BACKSLASH;
        const int GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT;

        const int ENTER = GLFW_KEY_ENTER;
        const int TAB = GLFW_KEY_TAB;
        const int BACKSPACE = GLFW_KEY_BACKSPACE;
        const int DELETE = GLFW_KEY_DELETE;
        const int INSERT = GLFW_KEY_INSERT;
        const int PAGE_UP = GLFW_KEY_PAGE_UP;
        const int PAGE_DOWN = GLFW_KEY_PAGE_DOWN;
        const int HOME = GLFW_KEY_HOME;
        const int END = GLFW_KEY_END;

        const int NUM_0 = GLFW_KEY_0;
        const int NUM_1 = GLFW_KEY_1;
        const int NUM_2 = GLFW_KEY_2;
        const int NUM_3 = GLFW_KEY_3;
        const int NUM_4 = GLFW_KEY_4;
        const int NUM_5 = GLFW_KEY_5;
        const int NUM_6 = GLFW_KEY_6;
        const int NUM_7 = GLFW_KEY_7;
        const int NUM_8 = GLFW_KEY_8;
        const int NUM_9 = GLFW_KEY_9;

        const int KEYPAD_0 = GLFW_KEY_KP_0;
        const int KEYPAD_1 = GLFW_KEY_KP_1;
        const int KEYPAD_2 = GLFW_KEY_KP_2;
        const int KEYPAD_3 = GLFW_KEY_KP_3;
        const int KEYPAD_4 = GLFW_KEY_KP_4;
        const int KEYPAD_5 = GLFW_KEY_KP_5;
        const int KEYPAD_6 = GLFW_KEY_KP_6;
        const int KEYPAD_7 = GLFW_KEY_KP_7;
        const int KEYPAD_8 = GLFW_KEY_KP_8;
        const int KEYPAD_9 = GLFW_KEY_KP_9;

        const int KEY_A = GLFW_KEY_A;
        const int KEY_B = GLFW_KEY_B;
        const int KEY_C = GLFW_KEY_C;
        const int KEY_D = GLFW_KEY_D;
        const int KEY_E = GLFW_KEY_E;
        const int KEY_F = GLFW_KEY_F;
        const int KEY_G = GLFW_KEY_G;
        const int KEY_H = GLFW_KEY_H;
        const int KEY_I = GLFW_KEY_I;
        const int KEY_J = GLFW_KEY_J;
        const int KEY_K = GLFW_KEY_K;
        const int KEY_L = GLFW_KEY_L;
        const int KEY_M = GLFW_KEY_M;
        const int KEY_N = GLFW_KEY_N;
        const int KEY_O = GLFW_KEY_O;
        const int KEY_P = GLFW_KEY_P;
        const int KEY_Q = GLFW_KEY_Q;
        const int KEY_R = GLFW_KEY_R;
        const int KEY_S = GLFW_KEY_S;
        const int KEY_T = GLFW_KEY_T;
        const int KEY_U = GLFW_KEY_U;
        const int KEY_V = GLFW_KEY_V;
        const int KEY_W = GLFW_KEY_W;
        const int KEY_X = GLFW_KEY_X;
        const int KEY_Y = GLFW_KEY_Y;
        const int KEY_Z = GLFW_KEY_Z;

        const int ESC = GLFW_KEY_ESCAPE;
        const int F1 = GLFW_KEY_F1;
        const int F2 = GLFW_KEY_F2;
        const int F3 = GLFW_KEY_F3;
        const int F4 = GLFW_KEY_F4;
        const int F5 = GLFW_KEY_F5;
        const int F6 = GLFW_KEY_F6;
        const int F7 = GLFW_KEY_F7;
        const int F8 = GLFW_KEY_F8;
        const int F9 = GLFW_KEY_F9;
        const int F10 = GLFW_KEY_F10;
        const int F11 = GLFW_KEY_F11;
        const int F12 = GLFW_KEY_F12;

        const int CAPSLOCK       = GLFW_KEY_CAPS_LOCK;

        const int SHIFT_LEFT     = GLFW_KEY_LEFT_SHIFT;
        const int SHIFT_RIGHT    = GLFW_KEY_RIGHT_SHIFT;

        const int CTRL_LEFT      = GLFW_KEY_LEFT_CONTROL;
        const int CTRL_RIGHT     = GLFW_KEY_RIGHT_CONTROL;

        const int ALT            = GLFW_KEY_LEFT_ALT;
        const int ALT_GR         = GLFW_KEY_RIGHT_ALT;

        const int SPACE          = GLFW_KEY_SPACE;

        const int ARROW_LEFT     = GLFW_KEY_LEFT;
        const int ARROW_UP       = GLFW_KEY_UP;
        const int ARROW_RIGHT    = GLFW_KEY_RIGHT;
        const int ARROW_DOWN     = GLFW_KEY_DOWN;

        const int PRINT_SCREEN   = GLFW_KEY_PRINT_SCREEN;
        const int PAUSE          = GLFW_KEY_PAUSE;
    }
}