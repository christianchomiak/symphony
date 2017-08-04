#include "UIRenderer.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>    // std::sort

namespace Symphony
{
    UIRenderer::UIRenderer()
    {        
        textShader       = Shader::GetShader("TEXT");
        backgroundShader = Shader::GetShader("TEXTBG");

        uiProjectionMatrix = glm::ortho(0.0f, (float)Screen::Width(), 0.0f, (float)Screen::Height());
        
        /*
        // Configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);*/
    }

    UIRenderer::~UIRenderer()
    {
        /*glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);*/
    }

    void UIRenderer::Render(const Scene* scene)
    {
        std::vector<OrderableObject> objs;

        PrepareObjects(scene->GetSceneUIRoot(), objs, false);
        std::sort(objs.begin(), objs.end(), OrderableObject::FarthestObjectFromCamera2D);

        RenderUI(objs);
    }

    void UIRenderer::RenderUI(const std::vector<OrderableObject>& objects)
    {
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        //glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
        //glBlendFunc(GL_ONE, GL_ZERO);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);


        glActiveTexture(GL_TEXTURE0);
        //glBindVertexArray(VAO);

        
        const Text2D* go;


        backgroundShader->Use();
        glUniformMatrix4fv(glGetUniformLocation(backgroundShader->ID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(uiProjectionMatrix));

        textShader->Use();
        glUniformMatrix4fv(glGetUniformLocation(textShader->ID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(uiProjectionMatrix));

        for (auto t : objects)
        {
            //TO-DO: create a new UIObject from which Text2D and others will derive from
            go = static_cast<const Text2D*>(t.obj);
            
            const glm::mat4x4& goMat = go->transform.GetWorldTransformMatrix();

            //Render background
            if (go->text.bgRenderMode == Text::BackgroundRenderMode::WHOLE_TEXT && go->text.bgColor != Color::CLEAR)
            {
                backgroundShader->Use();

                glUniformMatrix4fv(glGetUniformLocation(backgroundShader->ID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(goMat));
                
                const glm::vec4& bgColor = go->text.bgColor;
                
                glUniform4f(glGetUniformLocation(backgroundShader->ID(), "bgColor"), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
                
                go->RenderBackground();

                glUseProgram(0);
            }

            //Render foreground
            textShader->Use();

            glUniformMatrix4fv(glGetUniformLocation(textShader->ID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(goMat));

            glUniform4f(glGetUniformLocation(textShader->ID(), "foregroundColor"),
                        go->text.fgColor.r,
                        go->text.fgColor.g,
                        go->text.fgColor.b,
                        go->text.fgColor.a);

            const glm::vec4& bgColor = (go->text.bgRenderMode == Text::BackgroundRenderMode::PER_GLYPH)
                                     ? go->text.bgColor
                                     : Color::CLEAR;
            
            glUniform4f(glGetUniformLocation(textShader->ID(), "backgroundColor"), bgColor.r, bgColor.g, bgColor.b, bgColor.a);

            go->Render();
        }

        glUseProgram(0);
    }
    
    void UIRenderer::PrepareObjects(const GameObject* obj, std::vector<OrderableObject>& toRender, bool dontIgnoreCurrentObject)
    {
        if (obj == nullptr || !obj->enabled) return;

        if (dontIgnoreCurrentObject)
        {
            toRender.push_back(OrderableObject(obj, obj->transform.GetPosition().z));
        }
        
        for (GameObject* o : obj->GetChildren())
        {
            PrepareObjects(o, toRender, true);
        }
    }
}