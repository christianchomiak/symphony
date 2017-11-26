#include "TextureManager.h"

#include <GLEW/GL/glew.h>
#include <SOIL2/SOIL2.h>

#include <Debugging/Debugging.h>

namespace Symphony
{
    std::map<HashString, uint> TextureManager::texturePool;

    Texture TextureManager::LoadTexture(HashString textureAlias, const char* textureFilename, Texture::WrappingType typeOfWrapping,
                                        Texture::FilteringType filtering, bool flipY, Texture::Transparency transparency)
    {
        const uint textureId = textureAlias.GetHash();
        const Texture::WrappingType wrappingMode = transparency != Texture::Transparency::NONE
                                                 ? Texture::WrappingType::CLAMP_TO_EDGE
                                                 : typeOfWrapping;

        Texture newTexture = Texture(textureId, wrappingMode, filtering);
        auto id = texturePool[textureAlias];

        if (id == 0) //The texture doesn't exist
        {
            //SOIL_FLAG_GL_MIPMAPS
            //SOIL_FLAG_MIPMAPS

            if (flipY)
            {
                id = SOIL_load_OGL_texture(textureFilename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
            }
            else
            {
                id = SOIL_load_OGL_texture(textureFilename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
            }

            if (id == 0)
            {
                LogErrorF("SOIL loading error: %s", SOIL_last_result());
                LogErrorF("Couldn't load texture: [%s] in path [%s]", textureAlias.GetCString(), textureFilename);
                return newTexture;
            }
            else
            {
                texturePool[textureAlias] = id;
            }
        }

        newTexture.id = id;
        newTexture.transparency = transparency;
        
        return newTexture;
    }

    GLuint TextureManager::LoadSkybox(HashString  skyboxAlias,
                                      const char* skyboxPositiveX, const char* skyboxNegativeX,
                                      const char* skyboxPositiveY, const char* skyboxNegativeY,
                                      const char* skyboxPositiveZ, const char* skyboxNegativeZ)
    {
        if (texturePool.find(skyboxAlias) == texturePool.end())
        {
            GLuint newSkybox = SOIL_load_OGL_cubemap
            (
                skyboxPositiveX,
                skyboxNegativeX,
                skyboxPositiveY,
                skyboxNegativeY,
                skyboxPositiveZ,
                skyboxNegativeZ,
                SOIL_LOAD_RGB,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS
            );
            
            if (newSkybox == 0)
            {
                LogErrorF("SOIL loading error: %s", SOIL_last_result());
                LogErrorF("Couldn't load skybox: [%s]", skyboxAlias.GetCString());
            }

            return newSkybox;
        }

        return texturePool[skyboxAlias];
    }

    void TextureManager::FreeTexture(Texture& t)
    {
        glDeleteTextures(1, &t.id);
    }

    void TextureManager::FreeTexture(HashString textureAlias)
    {
        uint tID = texturePool[textureAlias];
        
        //TO-DO: probably this check won't be necessary as a texture id = 0
        //       is treated as null by OpenGL?
        if (tID != 0)
        {
            glDeleteTextures(1, &tID);
            texturePool.erase(textureAlias);
        }
    }
    
    void TextureManager::ClearTextureCache()
    {
        Log("[Deleting textures]");
        for (const auto& kv : texturePool)
        {
            LogF("\tDeleting texture: [%s]", kv.first.GetCString());
            glDeleteTextures(1, &kv.second);
        }
        texturePool.clear();
    }
}

