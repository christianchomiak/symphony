#include "Text.h"

#include "../../Rendering/Color.h"

namespace Symphony
{
    Text::Text()
        : scale(1.f), color(Color::WHITE), alignment(Alignment::CENTER)
    {
        SetContent("");
    }

    Text::Text(const std::string& content, const glm::vec4& color, float scale, Alignment alignment)
        : color(color), scale(scale), alignment(alignment)
    {
        SetContent(content);
    }

    Text::Text(const std::string& content, Alignment alignment)
        : Text(content, Color::WHITE, 1.f, alignment)
    {
        SetContent(content);
    }

    float Text::HorizontalPosition()
    {
        //float offset = 0.f;
        //size_t halfLength , oddity;
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

    float Text::VerticalPosition()
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
                if (ch.Bearing.y > dummyY) dummyY = (float)ch.Bearing.y;
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
                if (ch.Bearing.y < dummyY) dummyY = (float)ch.Bearing.y;
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

    void Text::SetContent(const std::string& newContent)
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
}