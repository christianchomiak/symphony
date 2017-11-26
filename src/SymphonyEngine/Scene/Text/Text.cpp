#include "Text.h"

#include <Rendering/Color.h>

namespace Symphony
{
    Text::Text()
        : font(nullptr), scale(1.f), fgColor(Color::WHITE), bgColor(Color::CLEAR), bgRenderMode(BackgroundRenderMode::WHOLE_TEXT),
          alignment(Alignment::CENTER)
    {
    }

    Text::Text(Font* f)
        : font(f), scale(1.f), fgColor(Color::WHITE), bgColor(Color::CLEAR), bgRenderMode(BackgroundRenderMode::WHOLE_TEXT),
          alignment(Alignment::CENTER)
    {
        SetContent("");
    }

    Text::Text(Font* f, const std::string& content, const glm::vec4& color, float scale, Alignment alignment)
        : font(f), fgColor(color), scale(scale), alignment(alignment), bgColor(Color::CLEAR), bgRenderMode(BackgroundRenderMode::WHOLE_TEXT)
    {
        SetContent(content);
    }

    Text::Text(Font* f, const std::string& content, Alignment alignment)
        : Text(f, content, Color::WHITE, 1.0f, alignment)
    {
        //SetContent(content);
    }

    float Text::HorizontalPosition()
    {
        if (!font) return 0.0f;

        //float offset = 0.f;
        //size_t halfLength , oddity;
        FontCharacter ch;

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
        if (!font) return 0.0f;

        FontCharacter ch;
        float dummyY;
        switch (alignment)
        {

        case Alignment::TOP_LEFT:
        case Alignment::TOP_CENTER:
        case Alignment::TOP_RIGHT:
            dummyY = FLT_MIN;
            for (size_t j = 0; j < content.size(); ++j)
            {
                ch = font->GetCharacter(content[j]); // FontCharacter::characters[content[j]];
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
                ch = font->GetCharacter(content[j]); //TextCharacter::characters[content[j]];
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

    void Text::Regenerate()
    {
        if (font)
        {
            pixelSize = 0.f;
            FontCharacter ch;
            for (size_t j = 0; j < content.size(); ++j)
            {
                ch = font->GetCharacter(content[j]); // TextCharacter::characters[content[j]];
                pixelSize += (ch.Advance >> 6) * scale;
            }
            UpdatePosition();
            RebuildBounds();
        }
    }

    void Text::RebuildBounds()
    {
        float currentX = 0.0f;
        float currentY = 0.0f;

        GLfloat minX, maxX;
        GLfloat minY, maxY;

        std::string::const_iterator c = content.begin();

        FontCharacter ch = font->GetCharacter(*c);

        GLfloat xpos = currentX + ch.Bearing.x * scale;
        GLfloat ypos = currentY + ch.Bearing.y * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        minX = xpos;
        minY = ypos - h;

        maxY = ypos;

        ++c;
        for (; c != content.end(); ++c)
        {
            currentX += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)

            ch = font->GetCharacter(*c);
            xpos = currentX + ch.Bearing.x * scale;
            ypos = currentY + ch.Bearing.y * scale;

            w = ch.Size.x * scale;
            h = ch.Size.y * scale;

            maxX = xpos + w;

            if (minY > ypos - h) minY = ypos - h;
            if (maxY < ypos)     maxY = ypos;
        }

        bounds[0].x = minX;
        bounds[0].y = maxY;

        bounds[1].x = maxX;
        bounds[1].y = maxY;

        bounds[2].x = minX;
        bounds[2].y = minY;

        bounds[3].x = maxX;
        bounds[3].y = minY;
    }
}