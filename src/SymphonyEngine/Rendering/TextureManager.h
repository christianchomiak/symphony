#pragma once

#include "Texture.h"
#include <map>

namespace Symphony
{
    //TO-DO: Perhaps this class should be a singleton? In its current state,
    //       it's not possible to create specialised TextureManagers that are independant
    //       from the target platform and rendering context.
    class TextureManager
    {
    public:
        static Texture LoadTexture(const char* textureFilename,
                                   Texture::WrappingType typeOfWrapping = Texture::WrappingType::REPEAT,
                                   bool filtering = false);
        
        //TO-DO: Figure out a better way to handle textures as they might
        //       be freed in OPENGL but other texture structs could still be
        //       pointing to the same, now-non-existent, position. 
        //       Furthermore, should `Textures` be created in the heap and,
        //       when no more references exist, they automatically delete their OPENGL counterpart?
        static void FreeTexture(Texture& t);
        static void FreeTexture(const char* textureFilename);
        static void ClearTextureCache();
    protected:
        static std::map<const char*, unsigned int> texturePool;
    };
}