#include "Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../Debugging/Debugging.h"

namespace Symphony
{
    std::map<const char*, Font*> Font::fontPool;

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

    //Static Manager

    bool Font::LoaderWorks()
    {
        FT_Library ft;

        if (FT_Init_FreeType(&ft))
        {
            Debug::LogError("ERROR::FREETYPE: Could not init FreeType Library");
            FT_Done_FreeType(ft);
            return false;
        }

        FT_Done_FreeType(ft);
        return true;
    }

    Font* Font::Load(const char* fontName, const char* fontPath)
    {
        //TO-DO: Also check for empty strings
        if (!fontPath)
        {
            Debug::LogError("ERROR: No font path was specified");
            return nullptr;
        }

        if (!fontName)
        {
            Debug::LogError("ERROR: No font name was specified");
            return nullptr;
        }

        if (Font::Exists(fontName))
        {
            Debug::LogWarningF("WARNING: There's an existing font named %s, returning that", fontName);
            return Font::Find(fontName);
        }

        //TO-DO: Should this be kept throught the lifetime of the FontManager?
        FT_Library ft;

        if (FT_Init_FreeType(&ft))
        {
            Debug::LogError("ERROR::FREETYPE: Could not init FreeType Library");
            return nullptr;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath, 0, &face))
        {
            Debug::LogErrorF("ERROR::FREETYPE: Failed to load font %s (path: %s)", fontName, fontPath);
            return nullptr;
        }

        Font* newFont = new Font(fontName);

        FT_Set_Pixel_Sizes(face, 0, 64);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                Debug::LogError("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }

            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RED,
                         face->glyph->bitmap.width,
                         face->glyph->bitmap.rows,
                         0,
                         GL_RED,
                         GL_UNSIGNED_BYTE,
                         face->glyph->bitmap.buffer);

            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Now store character for later use
            FontCharacter character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (unsigned int)face->glyph->advance.x,
                face->glyph->bitmap.pitch
            };

            newFont->AddGlyph(c, character);
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        fontPool[fontName] = newFont;

        Debug::LogF("Loaded font %s from path %s", fontName, fontPath);

        return newFont;
    }

    void Font::UnloadAll()
    {
        Debug::Log("[Deleting fonts]");
        for (const auto& kv : fontPool)
        {
            Debug::LogF("[Deleting font %s]", kv.first);
            delete kv.second;
        }
        fontPool.clear();
    }
}