#include "Renderer.h"

#define GLEW_STATIC
#include <GLEW/GL/glew.h> //GLEW must be included before any other GL-related header files

void Symphony::Renderer::ProcessTexture(const Texture& texture) const
{
    glBindTexture(GL_TEXTURE_2D, texture.id);

    //WRAPPING
    GLuint action;
    switch (texture.typeOfWrapping)
    {
    case Texture::WrappingType::REPEAT:
        action = GL_REPEAT;
        break;
    case Texture::WrappingType::MIRRORED_REPEAT:
        action = GL_MIRRORED_REPEAT;
        break;
    case Texture::WrappingType::CLAMP:
        action = GL_CLAMP;
        break;
    case Texture::WrappingType::CLAMP_TO_EDGE:
        action = GL_CLAMP_TO_EDGE;
        break;
    case Texture::WrappingType::CLAMP_TO_BORDER:
        action = GL_CLAMP_TO_BORDER;
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, action);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, action);
    
    //FILTERING
    //x axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.filter ? GL_LINEAR : GL_NEAREST);
    //y axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.filter ? GL_LINEAR : GL_NEAREST);

    //We can't unbind the texture as it'll be used during the rendering process
    //glBindTexture(GL_TEXTURE_2D, 0);
}
