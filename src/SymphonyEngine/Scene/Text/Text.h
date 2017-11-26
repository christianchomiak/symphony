#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <Rendering/UI/Font.h>

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

        enum class BackgroundRenderMode
        {
            PER_GLYPH,
            WHOLE_TEXT
        };

        glm::vec2 offset;
        glm::vec4 fgColor, bgColor;
        BackgroundRenderMode bgRenderMode;
        
        Text();
        Text(Font* f);
        Text(Font* f, const std::string& content, const glm::vec4& color, float scale, Alignment alignment = Alignment::CENTER);
        Text(Font* f, const std::string& content, Alignment alignment = Alignment::CENTER);

        glm::vec2 GetPosition() const;

        const std::string& GetContent() const;
        void SetContent(const std::string& newContent);
        
        Alignment GetAlignment() const;
        void SetAlignment(Alignment newAlignment);

        float GetScale() const;
        void SetScale(float newScale);

        Font* GetFont() const;
        void SetFont(Font* newFont);

        const void GetBounds(glm::vec3& bottomLeft, glm::vec3& bottomRight, glm::vec3& topLeft, glm::vec3& topRight) const
        {
            bottomLeft.x    = bounds[0].x;
            bottomLeft.y    = bounds[0].y;

            bottomRight.x   = bounds[1].x;
            bottomRight.y   = bounds[1].y;

            topLeft.x       = bounds[2].x;
            topLeft.y       = bounds[2].y;

            topRight.x      = bounds[3].x;
            topRight.y      = bounds[3].y;
        }

    protected:
        std::string content; //TO-DO: why not put this public?
        glm::vec2 position;
        Alignment alignment;
        float scale; //TO-DO: Eventually this should be a vec2, perhaps?
        float pixelSize;
        Font* font;

        glm::vec2 bounds[4]; //This is auto-generated

        void UpdatePosition();

        float HorizontalPosition();

        float VerticalPosition();

        void Regenerate();

        void RebuildBounds();
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

    inline void Text::SetFont(Font* newFont)
    {
        font = newFont;
        Regenerate();
    }

    inline Font* Text::GetFont() const
    {
        return font;
    }

    inline void Text::SetContent(const std::string& newContent)
    {
        content = newContent;
        Regenerate();
    }
}