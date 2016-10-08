#pragma once

#include <string>
#include <glm/vec4.hpp>

#include "TextCharacter.h"

namespace Symphony
{
    struct Text
    {
    public:
        enum class Alignment : char
        { 
            TOP_LEFT,    TOP_CENTER,    TOP_RIGHT,
            CENTER_LEFT, CENTER,        CENTER_RIGHT,
            BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
        };

        glm::vec4 color;
        glm::vec2 offset;
        
        Text();
        Text(const std::string& content, const glm::vec4& color, float scale, Alignment alignment = Alignment::CENTER);
        Text(const std::string& content, Alignment alignment = Alignment::CENTER);

        glm::vec2 GetPosition() const;

        const std::string& GetContent() const;
        void SetContent(const std::string& newContent);
        
        Alignment GetAlignment() const;
        void SetAlignment(Alignment newAlignment);

        float GetScale() const;
        void SetScale(float newScale);

    protected:
        std::string content; //TO-DO: why not put this public?
        glm::vec2 position;
        Alignment alignment;
        float scale; //TO-DO: Eventually this should be a vec2, perhaps?
        float pixelSize;

        void UpdatePosition();

        float HorizontalPosition();

        float VerticalPosition();
    };
    
    inline glm::vec2 Text::GetPosition() const
    {
        //return glm::vec3(HorizontalPosition(), VerticalPosition(), position.z);
        return position + offset;
    }

    inline const std::string& Text::GetContent() const
    {
        return content;
    }

    inline void Text::UpdatePosition()
    {
        position.x = HorizontalPosition();
        position.y = VerticalPosition();
    }

    inline float Text::GetScale() const
    {
        return scale;
    }

    inline void Text::SetScale(float newScale)
    {
        scale = newScale;
        UpdatePosition();
    }

    inline Text::Alignment Text::GetAlignment() const
    {
        return alignment;
    }

    inline void Text::SetAlignment(Alignment newAlignment)
    {
        alignment = newAlignment;
        UpdatePosition();
    }
}