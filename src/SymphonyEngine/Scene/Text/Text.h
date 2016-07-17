#pragma once

#include <string>
#include "TextCharacter.h"
#include "../../Rendering/Color.h"

namespace Symphony
{
    struct Text
    {
    public:
        enum class Alignment : char 
        { 
            TOP_LEFT, TOP_CENTER, TOP_RIGHT,
            CENTER_LEFT, CENTER, CENTER_RIGHT,
            BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
        };

        glm::vec4 color;
        glm::vec2 offset;
        
        Text()
            : scale(1.f), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
              alignment(Alignment::CENTER)
        {
            SetContent("");
        }

        Text(const std::string& content, const glm::vec4& color, float scale,
             Alignment alignment = Alignment::CENTER)
            : color(color), scale(scale), alignment(alignment)
        {
            SetContent(content);
        }
        
        Text(const std::string& content, Alignment alignment = Alignment::CENTER)
            : Text(content, Color::White(), 1.f, alignment)
        {
            SetContent(content);
        }

        glm::vec2 GetPosition() const
        {
            //return glm::vec3(HorizontalPosition(), VerticalPosition(), position.z);
            return position + offset;
        }

        void SetContent(const std::string& newContent)
        {
            content = newContent;
            pixelSize = 0.f;
            TextCharacter ch;
            for (size_t j = 0; j < content.size(); ++j)
            {
                ch = TextCharacter::characters[content[j]];
                pixelSize += (ch.Advance >> 6) * scale;
            }
            UpdatePosition();
        }

        const std::string& GetContent() const
        {
            return content;
        }
        
        void SetAlignment(Alignment newAlignment)
        {
            alignment = newAlignment;
            UpdatePosition();
        }
        
        void SetScale(float newScale)
        {
            scale = newScale;
            UpdatePosition();
        }

        float GetScale() const
        {
            return scale;
        }

    protected:
        std::string content; //TO-DO: why not put this public?
        glm::vec2 position;
        Alignment alignment;
        float scale; //TO-DO: Eventually this should be a vec2, perhaps?
        float pixelSize;

        void UpdatePosition()
        {
            position.x = HorizontalPosition();
            position.y = VerticalPosition();
        }

        float HorizontalPosition()
        {
            //float offset = 0.f;
            size_t halfLength, oddity;
            TextCharacter ch;

            switch (alignment)
            {
            case Alignment::TOP_LEFT:
            case Alignment::CENTER_LEFT:
            case Alignment::BOTTOM_LEFT:
                return 0.f; // position.x;
                break;

            case Alignment::CENTER:
            case Alignment::TOP_CENTER:
            case Alignment::BOTTOM_CENTER:
                /*for (size_t j = 0; j < content.size(); ++j)
                {
                ch = TextCharacter::characters[content[j]];
                offset += (ch.Advance >> 6) * scale;
                }*/

                return -pixelSize * 0.5f; //position.x -

                /*if (content.size() == 0) return position.x;

                halfLength = content.size() / 2;
                oddity = content.size() % 2;

                size_t i;
                for (i = 0; i < halfLength; ++i)
                {
                ch = TextCharacter::characters[content[i]];
                offset += (ch.Advance >> 6) * scale;
                }

                if (oddity != 0)
                {
                ch = TextCharacter::characters[content[i + 1]];
                offset += (ch.Advance >> 6) * scale * 0.5f;
                }

                return position.x - offset;*/
                break;
                
            case Alignment::TOP_RIGHT:
            case Alignment::CENTER_RIGHT:
            case Alignment::BOTTOM_RIGHT:
                return -pixelSize; //position.x -
                break;
            default:
                //TO-DO: Raise warning here
                return 0.f; // position.x;
                break;
            }
        }

        float VerticalPosition()
        {
            TextCharacter ch;
            float dummyY;
            switch (alignment)
            {

            case Alignment::TOP_LEFT:
            case Alignment::TOP_CENTER:
            case Alignment::TOP_RIGHT:
                dummyY = FLT_MIN;
                for (size_t j = 0; j < content.size(); ++j)
                {
                    ch = TextCharacter::characters[content[j]];
                    if (ch.Bearing.y > dummyY) dummyY = ch.Bearing.y;
                }
                return -dummyY * scale; //position.y -
                break;

            case Alignment::CENTER:
            case Alignment::CENTER_LEFT:
            case Alignment::CENTER_RIGHT:
                dummyY = FLT_MAX;
                for (size_t j = 0; j < content.size(); ++j)
                {
                    ch = TextCharacter::characters[content[j]];
                    if (ch.Bearing.y < dummyY) dummyY = ch.Bearing.y;
                }
                return -dummyY * 0.5f * scale; // position.y -

                break;

            case Alignment::BOTTOM_LEFT:
            case Alignment::BOTTOM_CENTER:
            case Alignment::BOTTOM_RIGHT:
                return 0.f; // position.y;
                break;

            default:
                //TO-DO: Raise warning here
                return 0.f; // position.y;
                break;
            }
        }
    };
}