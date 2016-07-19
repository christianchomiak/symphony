#include "Text2D.h"

namespace Symphony
{
    Text2D::Text2D()
    {
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        renderObject = new RenderObject(Mesh::TextMesh(), nullptr);
    }

    Text2D::Text2D(const Text& t)
        : text(t)
    {
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        renderObject = new RenderObject(Mesh::TextMesh(), nullptr);
    }
    
    Text2D::Text2D(const std::string& content)
        : text(Text(content))
    {
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        renderObject = new RenderObject(Mesh::TextMesh(), nullptr);
    }

    Text2D::~Text2D()
    {
    }

    void Text2D::Render() const
    {
        if (!renderObject || !renderObject->GetMesh()) return;

        Mesh* m = renderObject->GetMesh();
        //Shader* s = renderObject->GetShader();

        //s->Use();

        glm::vec3 startingPosition = transform.GetPosition() + glm::vec3(text.GetPosition(), 0.0f);
        float currentX = startingPosition.x;
        float currentY = startingPosition.y;

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.GetContent().begin(); c != text.GetContent().end(); ++c)
        {
            TextCharacter ch = TextCharacter::characters[*c];

            GLfloat xpos = currentX + ch.Bearing.x * text.GetScale();
            GLfloat ypos = currentY + ch.Bearing.y * text.GetScale();;

            GLfloat w = ch.Size.x * text.GetScale();
            GLfloat h = ch.Size.y * text.GetScale();
            
            glm::vec3 updatedVertices[4];
            updatedVertices[0].x = xpos;
            updatedVertices[0].y = ypos;
            updatedVertices[1].x = xpos + w;
            updatedVertices[1].y = ypos;
            updatedVertices[2].x = xpos;
            updatedVertices[2].y = ypos - h;
            updatedVertices[3].x = xpos + w;
            updatedVertices[3].y = ypos - h;
            m->UpdateVertices(updatedVertices, 4);
            
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            m->Render();

            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            currentX += (ch.Advance >> 6) * text.GetScale(); // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        //s->Release();
    }

}