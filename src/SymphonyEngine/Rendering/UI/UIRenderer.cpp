#include "UIRenderer.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

namespace Symphony
{
    UIRenderer::UIRenderer()
    {
        textMesh = Mesh::TextMesh();
        textShader = Shader::GetShader("TEXT");
        
        uiProjectionMatrix = glm::ortho(0.0f, (float)Screen::Width(), 0.0f, (float)Screen::Height());

        // Configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    UIRenderer::~UIRenderer()
    {
        delete textMesh;

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void UIRenderer::Render(const Scene* scene)
    {
        std::vector<PossibleObject> objs;

        PrepareObjects(scene->GetSceneUIRoot(), objs, false);

        RenderUI(objs);
    }

    void UIRenderer::RenderUI(const std::vector<PossibleObject>& objects)
    {
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

         //glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
        //glBlendFunc(GL_ONE, GL_ZERO);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        float x;
        textShader->Use();

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        glUniformMatrix4fv(glGetUniformLocation(textShader->ID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(uiProjectionMatrix));
        
        float currentX, currentY;
        const Text2D* go;
        for (auto t : objects)
        {
            //TO-DO: create a new UIObject from which Text2D and others will derive from
            go = static_cast<const Text2D*>(t.obj);

            glUniform4f(glGetUniformLocation(textShader->ID(), "textColor"), go->text.color.r, go->text.color.g, go->text.color.b, go->text.color.a);
            
            glm::vec3 startingPosition = go->transform.GetPosition() + glm::vec3(go->text.GetPosition(), 0.0f);
            currentX = startingPosition.x;
            currentY = startingPosition.y;

            // Iterate through all characters
            std::string::const_iterator c;
            for (c = go->text.GetContent().begin(); c != go->text.GetContent().end(); c++)
            {
                TextCharacter ch = TextCharacter::characters[*c];

                GLfloat xpos = currentX + ch.Bearing.x * go->text.GetScale();
                GLfloat ypos = currentY + ch.Bearing.y * go->text.GetScale();;

                GLfloat w = ch.Size.x * go->text.GetScale();
                GLfloat h = ch.Size.y * go->text.GetScale();

                // Update VBO for each character
                GLfloat vertices[4][4] = {
                    { xpos    , ypos    ,   0.0f, 0.0f },
                    { xpos + w, ypos    ,   1.0f, 0.0f },
                    { xpos    , ypos - h,   0.0f, 1.0f },
                    { xpos + w, ypos - h,   1.0f, 1.0f }
                };

                // Render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // Update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // Render quad
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


                // Update content of VBO memory
                /*glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // Render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);*/

                // Update VBO for each character
                /*glm::vec3 vertices[6];
                vertices[0] = glm::vec3(xpos, ypos + h, 0.0f);
                vertices[1] = glm::vec3(xpos, ypos, 0.0f);
                vertices[2] = glm::vec3(xpos + w, ypos, 0.0f);
                vertices[3] = glm::vec3(xpos, ypos + h, 0.0f);
                vertices[4] = glm::vec3(xpos + w, ypos, 0.0f);
                vertices[5] = glm::vec3(xpos + w, ypos + h, 0.0f);

                // Render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);

                glBindBuffer(GL_ARRAY_BUFFER, textMesh->GetVBO());
                glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(glm::vec3), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                textMesh->Render();*/

                // Update content of VBO memory
                /*glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // Render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);*/

                // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                currentX += (ch.Advance >> 6) * go->text.GetScale(); // Bitshift by 6 to get value in pixels (2^6 = 64)
            }
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void UIRenderer::PrepareObjects(const GameObject* obj, std::vector<PossibleObject>& toRender, bool dontIgnoreCurrentObject)
    {
        if (obj == nullptr || !obj->enabled) return;

        if (dontIgnoreCurrentObject)
        {
            toRender.push_back(PossibleObject(obj, 0.0f));
        }
        
        for (GameObject* o : obj->GetChildren())
        {
            PrepareObjects(o, toRender, true);
        }
    }
}