#pragma once

#include <map>
#include <glm/vec2.hpp>

#define GLEW_STATIC
#include <GLEW/GL/glew.h>

namespace Symphony
{
    struct FontCharacter
    {
        GLuint     TextureID;  // ID handle of the glyph texture
        glm::ivec2 Size;       // Size of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        GLuint     Advance;    // Offset to advance to next glyph
        int        Pitch;

        FontCharacter()
            : TextureID(0), Advance(0), Pitch(0) 
        { }

        FontCharacter(GLuint textureID, glm::ivec2 size, glm::ivec2 bearing, GLuint advance, int pitch)
            : TextureID(textureID), Size(size), Bearing(bearing), Advance(advance), Pitch(pitch)
        { }
    };

    class Font
    {
        public:
            Font();
            Font(const char* fontName);
            ~Font();
            
            inline void AddGlyph(GLchar glyph, FontCharacter& newFontCharacter)
            {
                characters[glyph] = newFontCharacter;
            }

            inline bool GlyphExists(GLchar glyph) const
            {
                return characters.find(glyph) != characters.end();
            }

            inline FontCharacter GetCharacter(GLchar character) const
            {
                auto iterator = characters.find(character);

                if (iterator != characters.end())
                {
                    return iterator->second;
                }
                
                return FontCharacter();
            }

        protected:
            std::string name;
            std::map<GLchar, FontCharacter> characters;
    };
}