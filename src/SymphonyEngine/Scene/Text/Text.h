#pragma once

#include <string>
#include "TextCharacter.h"

namespace Symphony
{
    struct Text
    {
    public:
        enum HorizontalCentering { LEFT, HCENTER, RIGHT };
        enum VerticalCentering { TOP, VCENTER, BOTTOM };
        
        float scale; //TO-DO: Eventually this should be a vec2, perhaps?
        glm::vec4 color;

        HorizontalCentering horizontalAlignment;
        VerticalCentering verticalAlignment;

        Text()
            : scale(1.f), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
              horizontalAlignment(HorizontalCentering::LEFT), verticalAlignment(VerticalCentering::BOTTOM)
        {
            SetContent("");
        }

        Text(const std::string& content, const glm::vec3& position, const glm::vec4& color, float scale,
             HorizontalCentering hAlignment = HorizontalCentering::LEFT, VerticalCentering vAlignment = VerticalCentering::BOTTOM)
            : position(position), color(color), scale(scale), horizontalAlignment(hAlignment), verticalAlignment(vAlignment)
        {
            SetContent(content);
        }

        glm::vec3 GetPosition()
        {
            return glm::vec3(HorizontalPosition(), VerticalPosition(), position.z);
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
        }

        const std::string& GetContent() const
        {
            return content;
        }
        
    protected:
        std::string content;
        glm::vec3 position;
        float pixelSize;

        float HorizontalPosition()
        {
            //float offset = 0.f;
            size_t halfLength, oddity;
            TextCharacter ch;

            switch (horizontalAlignment)
            {
            case Symphony::Text::LEFT:
                return position.x;
                break;
            case Symphony::Text::HCENTER:

                /*for (size_t j = 0; j < content.size(); ++j)
                {
                    ch = TextCharacter::characters[content[j]];
                    offset += (ch.Advance >> 6) * scale;
                }*/

                return position.x - pixelSize * 0.5f;

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
            case Symphony::Text::RIGHT:
                return position.x - pixelSize;
                break;
            default:
                break;
            }
        }

        float VerticalPosition()
        {
            TextCharacter ch;
            float dummyY;
            switch (verticalAlignment)
            {
            case Symphony::Text::TOP:
                dummyY = FLT_MIN;
                for (size_t j = 0; j < content.size(); ++j)
                {
                    ch = TextCharacter::characters[content[j]];
                    if (ch.Bearing.y > dummyY) dummyY = ch.Bearing.y;
                }
                return position.y - dummyY * scale;
                break;
            case Symphony::Text::VCENTER:
                dummyY = FLT_MAX;
                for (size_t j = 0; j < content.size(); ++j)
                {
                    ch = TextCharacter::characters[content[j]];
                    if (ch.Bearing.y < dummyY) dummyY = ch.Bearing.y;
                }
                return position.y - dummyY * 0.5f * scale;

                break;
            case Symphony::Text::BOTTOM:
                return position.y;
                break;
            default:
                break;
            }
        }
    };
}