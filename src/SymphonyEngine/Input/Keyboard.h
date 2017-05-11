#pragma once

#include <GLFW/glfw3.h>

#include "Input.h"

namespace Symphony
{
    enum Key
    {
        UNKOWN = GLFW_KEY_UNKNOWN,

        SEMICOLON   = GLFW_KEY_SEMICOLON,
        APOSTROPHE  = GLFW_KEY_APOSTROPHE,
        COMMA       = GLFW_KEY_COMMA,
        PERIOD      = GLFW_KEY_PERIOD,
        MINUS       = GLFW_KEY_MINUS,
        SLASH       = GLFW_KEY_SLASH,
        EQUAL       = GLFW_KEY_EQUAL,

        LEFT_BRACKET    = GLFW_KEY_LEFT_BRACKET,
        RIGHT_BRACKET   = GLFW_KEY_RIGHT_BRACKET,
        BACKSLASH       = GLFW_KEY_BACKSLASH,
        GRAVE_ACCENT    = GLFW_KEY_GRAVE_ACCENT,

        ENTER       = GLFW_KEY_ENTER,
        TAB         = GLFW_KEY_TAB,
        BACKSPACE   = GLFW_KEY_BACKSPACE,
        DEL         = GLFW_KEY_DELETE,
        INSERT      = GLFW_KEY_INSERT,
        PAGE_UP     = GLFW_KEY_PAGE_UP,
        PAGE_DOWN   = GLFW_KEY_PAGE_DOWN,
        HOME        = GLFW_KEY_HOME,
        END         = GLFW_KEY_END,

        NUM_0 = GLFW_KEY_0,
        NUM_1 = GLFW_KEY_1,
        NUM_2 = GLFW_KEY_2,
        NUM_3 = GLFW_KEY_3,
        NUM_4 = GLFW_KEY_4,
        NUM_5 = GLFW_KEY_5,
        NUM_6 = GLFW_KEY_6,
        NUM_7 = GLFW_KEY_7,
        NUM_8 = GLFW_KEY_8,
        NUM_9 = GLFW_KEY_9,

        PAD_0 = GLFW_KEY_KP_0,
        PAD_1 = GLFW_KEY_KP_1,
        PAD_2 = GLFW_KEY_KP_2,
        PAD_3 = GLFW_KEY_KP_3,
        PAD_4 = GLFW_KEY_KP_4,
        PAD_5 = GLFW_KEY_KP_5,
        PAD_6 = GLFW_KEY_KP_6,
        PAD_7 = GLFW_KEY_KP_7,
        PAD_8 = GLFW_KEY_KP_8,
        PAD_9 = GLFW_KEY_KP_9,

        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        ESC = GLFW_KEY_ESCAPE,
        F1  = GLFW_KEY_F1,
        F2  = GLFW_KEY_F2,
        F3  = GLFW_KEY_F3,
        F4  = GLFW_KEY_F4,
        F5  = GLFW_KEY_F5,
        F6  = GLFW_KEY_F6,
        F7  = GLFW_KEY_F7,
        F8  = GLFW_KEY_F8,
        F9  = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,

        CAPSLOCK = GLFW_KEY_CAPS_LOCK,

        SHIFT_LEFT  = GLFW_KEY_LEFT_SHIFT,
        SHIFT_RIGHT = GLFW_KEY_RIGHT_SHIFT,

        CTRL_LEFT   = GLFW_KEY_LEFT_CONTROL,
        CTRL_RIGHT  = GLFW_KEY_RIGHT_CONTROL,

        ALT     = GLFW_KEY_LEFT_ALT,
        ALT_GR  = GLFW_KEY_RIGHT_ALT,

        SPACE = GLFW_KEY_SPACE,

        ARROW_LEFT  = GLFW_KEY_LEFT,
        ARROW_UP    = GLFW_KEY_UP,
        ARROW_RIGHT = GLFW_KEY_RIGHT,
        ARROW_DOWN  = GLFW_KEY_DOWN,

        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        PAUSE = GLFW_KEY_PAUSE
    };

    class Keyboard
    {
        friend class InputManager;

    public:
        inline bool AnyKeyPressed() const { return anyKeyPressed; }

        bool KeyUp(Key key)      const;
        bool KeyPressed(Key key) const;
        bool KeyDown(Key key)    const;
        bool KeyHold(Key key)    const;
        //int KeyStatus(Key key)  const;
        
        inline bool CheckKeyID(Key id) const
        {
            return (id >= 0 && id < numberOfKeys);
        }

    protected:
        bool anyKeyPressed = false;
        int numberOfKeys;
        InputState* keys;

        Keyboard();
        ~Keyboard();
        void Update();
        void UpdateKey(int id, int state);
        void Reset();
    };
}