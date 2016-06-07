#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "Input.h"

namespace Symphony
{
    class Mouse
    {
        friend class InputManager;
    public:
        
        inline bool AnyButtonPressed() const { return anyButtonPressed; }

        bool ButtonPressed(int button) const;
        bool ButtonUp(int button)    const;
        bool ButtonDown(int button)  const;
        bool ButtonHold(int button)  const;
        
        inline double PositionX() const { return position.x; }
        inline double PositionY() const { return position.y; }
        inline glm::vec2 Position() const { return position; }        

        inline bool CheckButtonID(int id) const
        {
            return (id >= 0 && id < numberOfButtons);
        }
        
    protected:
        glm::vec2 position;
        int numberOfButtons;
        bool anyButtonPressed;
        InputState* buttons;

        Mouse();
        ~Mouse();

        void Reset();
        void Update();
        void UpdateButton(int id, int state);
    };
    
    namespace Button
    {
        const int LEFT   = GLFW_MOUSE_BUTTON_1;
        const int RIGHT  = GLFW_MOUSE_BUTTON_2;
        const int MIDDLE = GLFW_MOUSE_BUTTON_3;

        const int BTN_1 = GLFW_MOUSE_BUTTON_1;
        const int BTN_2 = GLFW_MOUSE_BUTTON_2;
        const int BTN_3 = GLFW_MOUSE_BUTTON_3;
        const int BTN_4 = GLFW_MOUSE_BUTTON_4;
        const int BTN_5 = GLFW_MOUSE_BUTTON_5;
        const int BTN_6 = GLFW_MOUSE_BUTTON_6;
        const int BTN_7 = GLFW_MOUSE_BUTTON_7;
        const int BTN_8 = GLFW_MOUSE_BUTTON_8;
    }
}