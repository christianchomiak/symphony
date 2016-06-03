#pragma once

#include <GLFW/glfw3.h>

namespace Symphony
{
    class Keyboard
    {
        friend class InputManager;
    public:
        enum KeyState { IDLE, DOWN, UP, HOLD };
        
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

        void Update();
    protected:
        bool anyKeyPressed = false;
        int numberOfKeys;
        KeyState* keys;

        void UpdateKey(int id, int state);
        void Reset();
        
    public:
        static const int KEY_UNKOWN     = GLFW_KEY_UNKNOWN;
        static const int KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE;
        static const int KEY_COMMA      = GLFW_KEY_COMMA;
        static const int KEY_MINUS      = GLFW_KEY_MINUS;
        static const int KEY_PERIOD     = GLFW_KEY_PERIOD;
        static const int KEY_SLASH      = GLFW_KEY_SLASH;

        static const int KEY_0 = GLFW_KEY_0;
        static const int KEY_1 = GLFW_KEY_1;
        static const int KEY_2 = GLFW_KEY_2;
        static const int KEY_3 = GLFW_KEY_3;
        static const int KEY_4 = GLFW_KEY_4;
        static const int KEY_5 = GLFW_KEY_5;
        static const int KEY_6 = GLFW_KEY_6;
        static const int KEY_7 = GLFW_KEY_7;
        static const int KEY_8 = GLFW_KEY_8;
        static const int KEY_9 = GLFW_KEY_9;

        static const int KEY_KEYPAD_0 = GLFW_KEY_KP_0;
        static const int KEY_KEYPAD_1 = GLFW_KEY_KP_1;
        static const int KEY_KEYPAD_2 = GLFW_KEY_KP_2;
        static const int KEY_KEYPAD_3 = GLFW_KEY_KP_3;
        static const int KEY_KEYPAD_4 = GLFW_KEY_KP_4;
        static const int KEY_KEYPAD_5 = GLFW_KEY_KP_5;
        static const int KEY_KEYPAD_6 = GLFW_KEY_KP_6;
        static const int KEY_KEYPAD_7 = GLFW_KEY_KP_7;
        static const int KEY_KEYPAD_8 = GLFW_KEY_KP_8;
        static const int KEY_KEYPAD_9 = GLFW_KEY_KP_9;

        static const int KEY_A = GLFW_KEY_A;
        static const int KEY_B = GLFW_KEY_B;
        static const int KEY_C = GLFW_KEY_C;
        static const int KEY_D = GLFW_KEY_D;
        static const int KEY_E = GLFW_KEY_E;
        static const int KEY_F = GLFW_KEY_F;
        static const int KEY_G = GLFW_KEY_G;
        static const int KEY_H = GLFW_KEY_H;
        static const int KEY_I = GLFW_KEY_I;
        static const int KEY_J = GLFW_KEY_J;
        static const int KEY_K = GLFW_KEY_K;
        static const int KEY_L = GLFW_KEY_L;
        static const int KEY_M = GLFW_KEY_M;
        static const int KEY_N = GLFW_KEY_N;
        static const int KEY_O = GLFW_KEY_O;
        static const int KEY_P = GLFW_KEY_P;
        static const int KEY_Q = GLFW_KEY_Q;
        static const int KEY_R = GLFW_KEY_R;
        static const int KEY_S = GLFW_KEY_S;
        static const int KEY_T = GLFW_KEY_T;
        static const int KEY_U = GLFW_KEY_U;
        static const int KEY_V = GLFW_KEY_V;
        static const int KEY_W = GLFW_KEY_W;
        static const int KEY_X = GLFW_KEY_X;
        static const int KEY_Y = GLFW_KEY_Y;
        static const int KEY_Z = GLFW_KEY_Z;

        static const int KEY_ESC = GLFW_KEY_ESCAPE;
        static const int KEY_F1 = GLFW_KEY_F1;
        static const int KEY_F2 = GLFW_KEY_F2;
        static const int KEY_F3 = GLFW_KEY_F3;
        static const int KEY_F4 = GLFW_KEY_F4;
        static const int KEY_F5 = GLFW_KEY_F5;
        static const int KEY_F6 = GLFW_KEY_F6;
        static const int KEY_F7 = GLFW_KEY_F7;
        static const int KEY_F8 = GLFW_KEY_F8;
        static const int KEY_F9 = GLFW_KEY_F9;
        static const int KEY_F10 = GLFW_KEY_F10;
        static const int KEY_F11 = GLFW_KEY_F11;
        static const int KEY_F12 = GLFW_KEY_F12;
        
        static const int KEY_SHIFT_LEFT     = GLFW_KEY_LEFT_SHIFT;
        static const int KEY_SHIFT_RIGHT    = GLFW_KEY_RIGHT_SHIFT;
        static const int KEY_CAPSLOCK       = GLFW_KEY_CAPS_LOCK;
        static const int KEY_CTRL_LEFT      = GLFW_KEY_LEFT_CONTROL;
        static const int KEY_CTRL_RIGHT     = GLFW_KEY_RIGHT_CONTROL;
        static const int KEY_ALT_GR         = GLFW_KEY_RIGHT_ALT;
        static const int KEY_ALT            = GLFW_KEY_LEFT_ALT;
        static const int KEY_SPACE          = GLFW_KEY_SPACE;

        static const int KEY_ARROW_LEFT     = GLFW_KEY_LEFT;
        static const int KEY_ARROW_UP       = GLFW_KEY_UP;
        static const int KEY_ARROW_RIGHT    = GLFW_KEY_RIGHT;
        static const int KEY_ARROW_DOWN     = GLFW_KEY_DOWN;

        static const int KEY_ENTER          = GLFW_KEY_ENTER;
        static const int KEY_TAB            = GLFW_KEY_TAB;
        static const int KEY_BACKSPACE      = GLFW_KEY_BACKSPACE;

        static const int KEY_UP     = GLFW_KEY_UP;
        static const int KEY_DOWN   = GLFW_KEY_DOWN;
        static const int KEY_LEFT   = GLFW_KEY_LEFT;
        static const int KEY_RIGHT  = GLFW_KEY_RIGHT;
    };
}