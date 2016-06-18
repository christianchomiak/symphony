#pragma once

#include <string>
#include "TextCharacter.h"

namespace Symphony
{
    struct Text
    {
    public:
        enum HorizontalAlignment { LEFT, HCENTER, RIGHT };
        enum VerticalAlignment { TOP, VCENTER, BOTTOM };

        std::string content;
        glm::vec3 color;
        float scale;

        HorizontalAlignment horizontalAlignment;
        VerticalAlignment verticalAlignment;

        Text()
            : content(""), scale(1.f), color(glm::vec3(1.0f, 1.0f, 1.0f)),
              horizontalAlignment(HorizontalAlignment::LEFT), verticalAlignment(VerticalAlignment::TOP)
        {
        }

        Text(const std::string& content, const glm::vec3& position, const glm::vec3& color, float scale,
             HorizontalAlignment hAlignment = HorizontalAlignment::LEFT, VerticalAlignment vAlignment = VerticalAlignment::TOP)
            : content(content), position(position), color(color), scale(scale), horizontalAlignment(hAlignment), verticalAlignment(vAlignment)
        {
        }

        glm::vec3 GetPosition()
        {
            return glm::vec3(HorizontalPosition(), VerticalPosition(), position.z);
        }

    protected:
        glm::vec3 position;

        float HorizontalPosition()
        {
            float offset = 0.f;
            switch (horizontalAlignment)
            {
            case Symphony::Text::LEFT:
                return position.x;
                break;
            case Symphony::Text::HCENTER:

                for (size_t i = 0; i < content.size() / 2; ++i)
                {
                    TextCharacter ch = TextCharacter::characters[content[i]];
                    offset += (ch.Advance >> 6) * scale;
                }

                //TO-DO: Take into account words that have an odd number of characters as in
                //       that case, the offset won't be totally correct

                return position.x - offset;
                break;
            case Symphony::Text::RIGHT:

                for (size_t i = 0; i < content.size(); ++i)
                {
                    TextCharacter ch = TextCharacter::characters[content[i]];
                    offset += (ch.Advance >> 6) * scale;
                }

                return position.x + offset;
                break;
            default:
                break;
            }
        }

        float VerticalPosition()
        {
            switch (verticalAlignment)
            {
            case Symphony::Text::TOP:
                return position.y;
                break;
            case Symphony::Text::VCENTER:
                break;
            case Symphony::Text::BOTTOM:
                break;
            default:
                break;
            }
        }
    };
}