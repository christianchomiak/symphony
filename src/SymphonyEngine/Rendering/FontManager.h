#pragma once

#include "Font.h"

namespace Symphony
{
    //TO-DO: Perhaps this class should be a singleton? In its current state,
    //       it's not possible to create specialised FontManagers that are independant
    //       from the target platform and rendering context.
    class FontManager
    {
        friend class SymphonyEngine;
    public:
        
        inline static bool FontExists(const char* fontName)
        {
            return fontPool.find(fontName) != fontPool.end();
        }

        inline static Font* GetFont(const char* fontName)
        {
            auto iterator = fontPool.find(fontName);

            if (iterator != fontPool.end())
            {
                return iterator->second;
            }

            return nullptr;
        }

    protected:
        static std::map<const char*, Font*> fontPool;
        
        static bool FontLibraryCanBeLoaded();

        static Font* LoadFont(const char* fontName, const char* fontPath);
        static void UnloadFonts();
    };
}