#include "TextureManager.h"

#include <GLEW/GL/glew.h>
#include <SOIL2/SOIL2.h>
#include <iostream>

namespace Symphony
{
    std::map<const char*, unsigned int> TextureManager::texturePool;

    Texture TextureManager::LoadTexture(const char* textureFilename, Texture::WrappingType typeOfWrapping,
                                        Texture::FilteringType filtering, bool flipY, Texture::Transparency transparency)
    {
        Texture newTexture = Texture(0, (transparency != Texture::Transparency::NONE ? Texture::WrappingType::CLAMP_TO_EDGE : typeOfWrapping), filtering);
        auto id = texturePool[textureFilename];

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
                std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
                std::cerr << "Couldn't load texture: " << textureFilename << std::endl;
                return newTexture;
            }
            else
            {
                texturePool[textureFilename] = id;
            }
        }

        newTexture.id = id;
        newTexture.transparency = transparency;
        
        return newTexture;
    }

    GLuint TextureManager::LoadSkybox(const char* skyboxName,
                                      const char* skyboxPositiveX, const char* skyboxNegativeX,
                                      const char* skyboxPositiveY, const char* skyboxNegativeY,
                                      const char* skyboxPositiveZ, const char* skyboxNegativeZ)
    {

        GLuint newSkybox;

        if (texturePool.find(skyboxName) == texturePool.end())
        {
            newSkybox = SOIL_load_OGL_cubemap
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
                std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
                std::cerr << "Couldn't load skybox: " << skyboxName << std::endl;
            }

            return newSkybox;
        }
        else
        {
            newSkybox = texturePool[skyboxName];
        }
        
        return newSkybox;
    }

    void TextureManager::FreeTexture(Texture& t)
    {
        glDeleteTextures(1, &t.id);
    }

    void TextureManager::FreeTexture(const char* textureFilename)
    {
        auto tID = texturePool[textureFilename];
        
        //TO-DO: probably this check won't be necessary as a texture id = 0
        //       is treated as null by OpenGL?
        if (tID != 0)
        {
            glDeleteTextures(1, &tID);
            texturePool.erase(textureFilename);
        }
    }

    void TextureManager::ClearTextureCache()
    {
        std::cout << "[Deleting textures]" << std::endl;
        for (const auto& kv : texturePool)
        {
            std::cout << "\tDeleting texture: " << kv.first << std::endl;
            glDeleteTextures(1, &kv.second);
        }
        texturePool.clear();
    }
}

