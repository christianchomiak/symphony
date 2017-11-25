#pragma once

#include <map>
#include "Texture.h"
#include "Skybox.h"

#include "../../Utilities/HashString.h"

namespace Symphony
{
    //TO-DO: Perhaps this class should be a singleton? In its current state,
    //       it's not possible to create specialised TextureManagers that are independant
    //       from the target platform and rendering context.
    class TextureManager
    {
    public:
        static Texture LoadTexture(HashString alias,
                                   const char* textureFilename,
                                   Texture::WrappingType typeOfWrapping = Texture::WrappingType::REPEAT,
                                   Texture::FilteringType filtering = Texture::FilteringType::NEAREST, bool flipY = true, Texture::Transparency transparency = Texture::Transparency::NONE);
        
        static uint LoadSkybox(HashString  skyboxAlias,
                               const char* skyboxPositiveX, const char* skyboxNegativeX,
                               const char* skyboxPositiveY, const char* skyboxNegativeY,
                               const char* skyboxPositiveZ, const char* skyboxNegativeZ);

        //TO-DO: Figure out a better way to handle textures as they might
        //       be freed in OPENGL but other texture structs could still be
        //       pointing to the same, now-non-existent, position. 
        //       Furthermore, should `Textures` be created in the heap and,
        //       when no more references exist, they automatically delete their OPENGL counterpart?
        static void FreeTexture(Texture& t);
        static void FreeTexture(HashString textureAlias);
        static void ClearTextureCache();
    protected:
        static std::map<HashString, uint> texturePool;
    };
}