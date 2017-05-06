#include "Font.h"

namespace Symphony
{

    Font::Font()
        : Font("NewFont")
    {
    }

    Font::Font(const char* fontName)
        : name(fontName)
    {
    }

    Font::~Font()
    {
        for (const auto& kv : characters)
        {
            glDeleteTextures(1, &kv.second.TextureID);
        }
    }
}