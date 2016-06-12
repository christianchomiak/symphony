#include "TestScene.h"

#include "SimpleRenderer.h"
#include "ComplexRenderer.h"
#include "../SymphonyEngine/Debugging/Debugging.h"
#include "../SymphonyEngine/Input/InputManager.h"

#include "../SymphonyEngine/Scene/Camera/PerspectiveCamera.h"
#include "../SymphonyEngine/Scene/Camera/OrthographicCamera.h"

#include "../SymphonyEngine/Scene/Light/PointLight.h"
#include "../SymphonyEngine/Scene/Light/DirectionalLight.h"
#include "../SymphonyEngine/Scene/Light/Spotlight.h"

#include "FreeRoamCamera.h"

#include "../SymphonyEngine/Rendering/TextureManager.h"

#include "../SymphonyEngine/Scene/Text/TextCharacter.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

TestScene::TestScene()
{
    name = "TEST_SCENE1";
    textMesh = Mesh::TextMesh();
    textShader = Shader::GetShader("TEXT");

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

TestScene::~TestScene()
{
    delete renderer;
    delete textMesh;
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TestScene::Initialise()
{
    renderer = new ComplexRenderer();

    FreeRoamCamera* cam = new FreeRoamCamera();
    cam->name = "Camera";
    //RegisterCamera(cam);
    //emptyGo->AddChild(cam);
    cam->transform.Translate(0, 150, -30);
    //cam->transform.Rotate(0, 90, 0);
    AddGameObject(cam);
    cam->SetSkybox(TextureManager::LoadSkybox("SKY",
        "../../resources/Textures/Skybox/right.jpg",
        "../../resources/Textures/Skybox/left.jpg",
        "../../resources/Textures/Skybox/top.jpg",
        "../../resources/Textures/Skybox/bottom.jpg",
        "../../resources/Textures/Skybox/back.jpg",
        "../../resources/Textures/Skybox/front.jpg"),
        Shader::GetShader("SKYBOX"));

    Light* light;

    int lightType = 0;
    if (lightType < 0)
    {
        light = new PointLight(glm::vec3(0.0f, 0, 0.0f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
            50.f, 1.0f, 0.014f, 0.0007f);
        light->name = "Point Light";

        cam->AddChild(light);
        RegisterLight(light);
    }
    else if (lightType == 0)
    {
        light = new DirectionalLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f));
        light->name = "Directional Light";
        /*cam->AddChild(dLight);
        RegisterLight(dLight);*/

        AddGameObject(light);
        light->transform.SetLocalPosition(0, 100, -10.f);
        light->transform.SetLocalRotation(45, 0, 0);
    }
    else
    {
        light = new Spotlight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
            12.5f, 15.f, 1.0f, 0.007, 0.0002f);
        light->name = "Spotlight";

        cam->AddChild(light);
        RegisterLight(light);
        light->transform.SetLocalRotation(0, 180, 0);
        /*AddGameObject(light);
        light->transform.SetLocalPosition(0, 50, -10.f);
        light->transform.SetLocalRotation(15, 0, 0);*/
    }

    GameObject* coord = new GameObject();
    coord->name = "Coordinate System";
    //AddGameObject(coord);
    coord->AddRenderObject(new RenderObject(Mesh::CoordinateSystem(), Texture(), Shader::GetShader("UNLIT_COLOR")));
    //coord->transform.SetLocalPosition(0, 150, -10.f);
    light->AddChild(coord);

    GameObject* cube = new GameObject();
    cube->name = "Cube";
    AddGameObject(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            TextureManager::LoadTexture("../../resources/Textures/window.png", Texture::WrappingType::CLAMP, Texture::FilteringType::LINEAR, true, Texture::Transparency::SEMI),
            Shader::GetShader("UNLIT_TEXTURE")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);

    //GetPosition doesn't work at this stage because the scene tree hasn't been updated yet.
    //TO-DO: find a workaround to this issue.
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());

    cube->transform.Translate(0, 0, 5);
    cube->transform.Scale(5.f);
    /*cube->GetRenderObject()->material = Material(glm::vec3(1.f, 1.f, 1.f),          //Ambient
    glm::vec3(1.f, 1.f, 1.f),          //Diffuse
    glm::vec3(1.f, 1.f, 1.f),          //Specular
    0.1f);                             //Shininess
    */

    cube = new GameObject();
    cube->name = "Cube2";
    AddGameObject(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            Texture(), //TextureManager::LoadTexture("../../resources/Textures/window.png", Texture::WrappingType::CLAMP, Texture::FilteringType::LINEAR, true, Texture::Transparency::SEMI),
            Shader::GetShader("REFLECTIVE")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());
    cube->transform.Translate(0, 0, 15);
    cube->transform.Scale(5.f);

    cube = new GameObject();
    cube->name = "Cube3";
    AddGameObject(cube);
    cube->AddRenderObject(
        new RenderObject(Mesh::Cube(),
            TextureManager::LoadTexture("../../resources/Textures/grass.png", Texture::WrappingType::CLAMP, Texture::FilteringType::NEAREST, true, Texture::Transparency::FULL),
            Shader::GetShader("TRANSPARENT")));
    cube->GetRenderObject()->SetBoundingRadius(1.5f);
    cube->transform.SetLocalPosition(light->transform.GetLocalPosition());
    cube->transform.Translate(0, 0, 25);
    cube->transform.Scale(5.f);



    GameObject* hMap = new GameObject();
    hMap->name = "Height Map";
    AddGameObject(hMap);
    hMap->AddRenderObject(
        new RenderObject(Mesh::HeightMap("../../resources/Textures/hm2.png", 16.f, 16.f, 1000.f),
            TextureManager::LoadTexture("../../resources/Textures/hmTexture.jpg", Texture::WrappingType::REPEAT, Texture::FilteringType::TRILINEAR),
            Shader::GetShader("PHONG")));
    hMap->transform.SetLocalPosition(0, 0, -100);
    hMap->transform.Scale(0.1f);


    /*PerspectiveCamera* cam = new PerspectiveCamera(45.f);
    //OrthographicCamera* cam = new OrthographicCamera(-1, 1, 1, -1);
    cam->name = "Camera";
    AddGameObject(cam);*/

    txt = new Text("Symphony Engine", glm::vec3(25, 25, 1.0f), glm::vec3(1.f, 1.f, 1.f), 1.f);
    AddText(txt);
    //AddText(new Text("Christian Chomiak", glm::vec3(540.f, 570.f, 0.5f), glm::vec3(0.3, 0.7f, 0.9f), 0.1f));
}

void TestScene::Clean()
{
    delete root;

    for (auto t : uiText)
    {
        delete t;
    }
}

void TestScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    //txt->content = std::to_string(deltaTime).c_str();
}

void TestScene::Render()
{
    if (renderer)
    {
        renderer->Render(root, cameras, lights);
    }
    
    if (uiText.size() == 0) return;

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

    glm::mat4 proj = glm::ortho(0.0f, (float)Screen::Width(), 0.0f, (float)Screen::Height());
    glUniformMatrix4fv(glGetUniformLocation(textShader->ID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(proj));

    for (auto t : uiText)
    {
        glUniform3f(glGetUniformLocation(textShader->ID(), "textColor"), t->color.x, t->color.y, t->color.z);
        x = t->position.x;
        // Iterate through all characters
        std::string::const_iterator c;
        for (c = t->content.begin(); c != t->content.end(); c++)
        {
            TextCharacter ch = TextCharacter::characters[*c];

            GLfloat xpos = x + ch.Bearing.x * t->scale;
            GLfloat ypos = t->position.y + (ch.Bearing.y) * t->scale;

            GLfloat w = ch.Size.x * t->scale;
            GLfloat h = ch.Size.y * t->scale;
                        

            // Update VBO for each character
            GLfloat vertices[4][4] = {
                { xpos    , ypos    ,   0.0f, 0.0f },
                { xpos + w, ypos    ,   1.0f, 0.0f },
                { xpos    , ypos - h,   0.0f, 1.0f  },
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
            x += (ch.Advance >> 6) * t->scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
