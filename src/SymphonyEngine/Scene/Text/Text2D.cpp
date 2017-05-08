#include "Text2D.h"

#include "../../Rendering/MutableMesh.h"

namespace Symphony
{
    Text2D::Text2D()
    {
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        renderObject = new RenderObject((Mesh*)Mesh::TextMesh(), nullptr);
    }

    Text2D::Text2D(const Text& t)
        : text(t)
    {
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        renderObject = new RenderObject((Mesh*)Mesh::TextMesh(), nullptr);
    }
    
    Text2D::Text2D(Font* font, const std::string& content)
        : text(Text(font, content))
    {
        //TO-DO: Figure out a way to handle the Shader or Mesh being changed outside the class
        renderObject = new RenderObject((Mesh*)Mesh::TextMesh(), nullptr);
    }

    Text2D::~Text2D()
    {
    }

    void Text2D::RenderBackground() const
    {
        if (!renderObject || !renderObject->GetMesh()) return;

        MutableMesh* m = static_cast<MutableMesh*>(renderObject->GetMesh());

        glm::vec3 startingPosition = glm::vec3(text.GetPosition(), 0.0f); //transform.GetPosition() + 

        glm::vec3 updatedVertices[4];

        text.GetBounds(updatedVertices[0], updatedVertices[1], updatedVertices[2], updatedVertices[3]);

        for (size_t i = 0; i < 4; ++i)
        {
            updatedVertices[i].x += startingPosition.x;
            updatedVertices[i].y += startingPosition.y;
        }

        m->UpdateVertices(updatedVertices, 4);

        // Render background over quad
        m->Render();
        
        glBindVertexArray(0); //TO-DO: This could be removed as it's called at the end of Mesh::Render()
    }

    void Text2D::Render() const
    {
        if (!renderObject || !renderObject->GetMesh()) return;
        
        MutableMesh* mesh = static_cast<MutableMesh*>(renderObject->GetMesh());

        glm::vec3 startingPosition = glm::vec3(text.GetPosition(), 0.0f); //transform.GetPosition() + 
        float currentX = startingPosition.x;
        float currentY = startingPosition.y;

        float textScale = text.GetScale();

        // Iterate through all characters 
        std::string::const_iterator c;
        for (c = text.GetContent().begin(); c != text.GetContent().end(); ++c)
        {
            FontCharacter ch = text.GetFont()->GetCharacter(*c); // TextCharacter::characters[*c];

            GLfloat xpos = currentX + ch.Bearing.x * textScale;
            GLfloat ypos = currentY + ch.Bearing.y * textScale;

            GLfloat w = ch.Size.x * textScale;
            GLfloat h = ch.Size.y * textScale;
            
            glm::vec3 updatedVertices[4];

            updatedVertices[0].x = xpos;
            updatedVertices[0].y = ypos;

            updatedVertices[1].x = xpos + w;
            updatedVertices[1].y = ypos;

            updatedVertices[2].x = xpos;
            updatedVertices[2].y = ypos - h;

            updatedVertices[3].x = xpos + w;
            updatedVertices[3].y = ypos - h;

            mesh->UpdateVertices(updatedVertices, 4);
            
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            mesh->Render();

            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            currentX += (ch.Advance >> 6) * textScale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        
        glBindVertexArray(0); //TO-DO: This could be removed as it's called at the end of Mesh::Render()
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}