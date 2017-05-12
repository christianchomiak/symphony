#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include "Input.h"

namespace Symphony
{
    class Mouse
    {
        friend class InputManager;
    //public:
    //    float filter; //Not currently used

    public:
        bool AnyButtonPressed() const;

        bool      ButtonUp(int button)  const;
        bool    ButtonDown(int button)  const;
        bool    ButtonHold(int button)  const;
        bool ButtonPressed(int button)  const;
        
        double PositionX() const;
        double PositionY() const;
        double ScrollWheel() const;

        glm::vec2      Position() const;
        glm::vec2 DeltaPosition() const;
        
        bool CheckButtonID(int id) const;
        void SetSensitivity(float sensitivity);

    protected:
        int numberOfButtons;
        bool anyButtonPressed;

        glm::vec2 position;
        glm::vec2 deltaPosition;
        glm::dvec2 scrollWheel;

        float sensitivity;

        InputState* buttons;

        Mouse();
        ~Mouse();

        void Reset();
        void Update();
        void UpdateButton(int id, int state);
        void UpdatePosition(float newX, float newY);
        
        inline void UpdateScroll(double deltaX, double deltaY)
        {
            scrollWheel.x += deltaX;
            scrollWheel.y += deltaY;
        }
    };

    inline bool Mouse::AnyButtonPressed() const
    { 
        return anyButtonPressed;
    }


    inline double Mouse::ScrollWheel() const
    {
        return scrollWheel.y;
    }

    inline double Mouse::PositionX() const
    { 
        return position.x;
    }
    
    inline double Mouse::PositionY() const
    { 
        return position.y;
    }

    inline glm::vec2 Mouse::Position() const
    {
        return position;
    
    }

    inline glm::vec2 Mouse::DeltaPosition() const
    {
        return deltaPosition;
    }
    
    inline bool Mouse::CheckButtonID(int id) const
    {
        return (id >= 0 && id < numberOfButtons);
    }
    
    enum MButton
    {
        BTN_LEFT    = GLFW_MOUSE_BUTTON_1,
        BTN_RIGHT   = GLFW_MOUSE_BUTTON_2,
        BTN_MIDDLE  = GLFW_MOUSE_BUTTON_3,

        BTN_1 = GLFW_MOUSE_BUTTON_1,
        BTN_2 = GLFW_MOUSE_BUTTON_2,
        BTN_3 = GLFW_MOUSE_BUTTON_3,
        BTN_4 = GLFW_MOUSE_BUTTON_4,
        BTN_5 = GLFW_MOUSE_BUTTON_5,
        BTN_6 = GLFW_MOUSE_BUTTON_6,
        BTN_7 = GLFW_MOUSE_BUTTON_7,
        BTN_8 = GLFW_MOUSE_BUTTON_8
    };
}