#pragma once

#include <map>
#include <glm/vec2.hpp>

#define GLEW_STATIC
#include <GLEW/GL/glew.h>

namespace Symphony
{
    struct TextCharacter {
        GLuint     TextureID;  // ID handle of the glyph texture
        glm::ivec2 Size;       // Size of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        GLuint     Advance;    // Offset to advance to next glyph
        int        Pitch;

        static std::map<GLchar, TextCharacter> characters;
    };
}