#include "SymphonyEngine.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <sstream>
#include <fstream>

#include "../IO/DataReader.h"
#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"
#include "../Rendering/Shader.h"
#include "../Rendering/TextureManager.h"
#include "../Scene/Text/TextCharacter.h"

namespace Symphony
{
    SymphonyEngine* SymphonyEngine::instance = nullptr;
    const char* SymphonyEngine::version = "Symphony Engine - v0.1.0 \"Bittersweet\"";

    SymphonyEngine::SymphonyEngine()
    {
        currentScene    = nullptr;
        window          = nullptr;
        running         = true;
        initialised     = false;
        changeSceneFlag = true;
    }

    SymphonyEngine::~SymphonyEngine()
    {
        for (Scene* s : scenes)
        {
            delete s;
        }
        delete window;
    }
        
    bool SymphonyEngine::Initialise(const char* commandLineFilename)
    {
        Window::WindowProperties wProperties = Window::WindowProperties();
        wProperties.cursorMode  = Window::CursorMode::DISABLED;
        wProperties.borderless  = false;
        wProperties.fullscreen  = false;
        wProperties.width       = 1280;
        wProperties.height      = 720;
        wProperties.maximised   = false;
        wProperties.resizeable  = true;
        wProperties.title = "Symphony Engine demo";
        wProperties.switchableToOtherModes = false;
        
        return Initialise(wProperties, commandLineFilename);
    }
    
    bool SymphonyEngine::Initialise(const char* configFilename, const char* commandLineFilename)
    {
        return Initialise(Window::WindowProperties::CreateFromFile(configFilename), commandLineFilename);
    }
    
    bool SymphonyEngine::Initialise(const Window::WindowProperties& windowProperties, const char* commandLineFilename)
    {
        std::cout.setf(std::ios::boolalpha);
        std::cout << std::endl << SymphonyEngine::version << std::endl << std::endl;
        
        //window = new Window(Version(), 800, 600, true, true, true, false);
        //window = Window::CreateFullScreenWindow(Version(), 1920, 1080, false);
        window = new Window(windowProperties);
        
        initialised = window->Initialise();

        if (!initialised)
        {
            delete window;
            window = nullptr;
            return false;
        }

        LoadCommandLineArguments(commandLineFilename);
        LoadFonts();

        return initialised;
    }    

    void SymphonyEngine::Run()
    {
        if (!initialised)
        {
            Debug::LogError("Symphony Engine hasn't been initialised yet");
            return;
        }

        float deltaTime;

        //TO-DO: Code regarding FPS check could be enabled/disabled by the user
        /*int numberOfFrames = 0;
        float frameStartTime, frameEndTime = 0.0f, frameTotalTime;
        float nextTimeLap = frameEndTime + 1.0f;
        std::stringstream ss;*/
        
        ChangeScene(0);
        LoadNextScene();
        
        if (!currentScene)
        {
            Debug::LogError("No initial scene was found");
            running = false;
        }
        
        Mouse* mouse        = InputManager::GetMouse();
        Keyboard* keyboard  = InputManager::GetKeyboard();
        while (running)
        {
            InputManager::Update();
            window->Update();

            if (changeSceneFlag)
            {
                LoadNextScene();
            }
            
            Time::Update();
            deltaTime = Time::DeltaTime(); //gameTimer->GetDeltaTime();
            //window->SetTitle(std::to_string(deltaTime).c_str());
            
            //frameStartTime = gameTimer->GetMS();
                        
            if (currentScene)
            {
                currentScene->Update(deltaTime);
                currentScene->Render();
            }


            /*if (keyboard->KeyDown(Keyboard::KEY_SPACE))
            {
                window->ChangeMode();
            }*/

            /*Debug::Log("");
            _WATCHPOINT*/
            //running = false;
            
            //TO-DO: Code regarding FPS check could be enabled/disabled by the user
            //Frame-rendering performance check
            /*frameEndTime = gameTimer->GetMS();
            frameTotalTime = frameEndTime - frameStartTime;
            ++numberOfFrames;
            if (nextTimeLap - frameEndTime <= 0.0f)
            {
                ss.clear();
                ss.str("FPS: ");
                ss << "FPS: " << (1000.0 / double(frameTotalTime)) << " | ms/frame: " << frameTotalTime << " | deltaTime: " << deltaTime;
                //windowManager->SetWindowTitle(ss.str().c_str());

                numberOfFrames = 0;
                nextTimeLap = frameEndTime + 100.0f;
            }*/
            
            window->SwapBuffers();
            running &= !window->Closed() && !keyboard->KeyDown(Key::ESC);
        }

        Unload();

        Debug::LogF("Symphony Engine has now finished execution");
    }

    void SymphonyEngine::AddScene(Scene* newScene)
    {
        if (newScene)
        {
            newScene->SetID(scenes.size());
            scenes.push_back(newScene);
            return;
        }

        Debug::LogWarningF("Trying to add a null scene to the engine");
    }
    
    void SymphonyEngine::NextScene()
    {
        ChangeScene(currentScene->GetID() + 1);
    }

    void SymphonyEngine::ChangeScene(std::string sceneName)
    {
        Scene* newScene = nullptr;
        for (size_t i = 0; i < scenes.size(); ++i)
        {
            if (scenes[i]->GetName() == sceneName)
            {
                newScene = scenes[i];
            }
        }
        
        if (!newScene)
        {
            Debug::LogErrorF("Scene %s doesn't exist", sceneName);
            return;
        }
        
        ChangeScene(newScene->GetID());
    }

    void SymphonyEngine::ChangeScene(unsigned int newSceneID)
    {
        if (scenes.size() == 0)
        {
            Debug::LogError("No scenes are registered in the engine");
            return;
        }
        else if (newSceneID >= scenes.size())
        {
            Debug::LogErrorF("Error trying to load scene #%d, only %d scene(s) exist", newSceneID, scenes.size());
            return;
        }
        nextSceneID = newSceneID;
        changeSceneFlag = true;
    }
    
    void SymphonyEngine::LoadShader(const char* shaderName,
                                    const vector<const char*>& attributes, const vector<const char*>& uniforms,
                                    const char* vertexShaderFilename, const char* fragmentShaderFilename,
                                    const char* geometryShaderFilename) const
    {
        Shader::CreateNewShader(shaderName, attributes, uniforms, vertexShaderFilename, fragmentShaderFilename, geometryShaderFilename);
    }

    void SymphonyEngine::LoadNextScene()
    {
        changeSceneFlag = false;

        if (currentScene)
        {
            currentScene->Clean();
        }

        currentScene = scenes[nextSceneID];
        currentScene->Initialise();
    }
    
    void SymphonyEngine::Unload()
    {
        //These could be done on the detructor of the engine but
        //I can't find any reason not to do it in here, before that.
        Shader::DeleteAllShaders();
        TextureManager::ClearTextureCache();
    }
    
    void SymphonyEngine::LoadFonts()
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            Debug::LogError("ERROR::FREETYPE: Could not init FreeType Library");
        }
        
        FT_Face face;
        if (FT_New_Face(ft, "../../resources/Fonts/arial.ttf", 0, &face))
        {
            Debug::LogError("ERROR::FREETYPE: Failed to load font");
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                Debug::LogError("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }

            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Now store character for later use
            TextCharacter character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (unsigned int)face->glyph->advance.x,
                face->glyph->bitmap.pitch
            };
            
            TextCharacter::characters.insert(std::pair<GLchar, TextCharacter>(c, character));
        }
        
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void SymphonyEngine::LoadShaders(const char* filename)
    {
        if (filename == nullptr)
        {
            Debug::LogError("No filename was specified, cannot load any shaders");
            return;
        }
        
        tinyxml2::XMLDocument shadersFile;

        if (!ValidateXmlLoading(filename, shadersFile.LoadFile(filename)))
        {
            Debug::LogError("Cannot load any shaders");
            return;
        }

        //tinyxml2::XMLElement* shadersData = doc.FirstChildElement("SymphonyShaders")->FirstChildElement("WindowData");
        
        tinyxml2::XMLElement* root = shadersFile.FirstChildElement("SymphonyShaders");

        if (!root)
        {
            Debug::LogErrorF("Could not find the root SymphonyShaders property in \"%s\". Aborting.", filename);
            return;
        }

        //Check if a global path to the shaders was specified
        const char* globalPath = GetTextFromXmlElement(root, "DefaultPath");
        
        tinyxml2::XMLElement* shadersData = root->FirstChildElement("Shaders");

        if (!shadersData)
        {
            Debug::LogErrorF("Could not find any shader data in \"%s\". Aborting.", filename);
            return;
        }

        const char* fileExtension = GetTextFromXmlElement(root, "FileExtension");

        if (!fileExtension)
        {
            Debug::LogErrorF("Could not find any file extension specified in \"%s\". Aborting.", filename);
            return;
        }

        tinyxml2::XMLElement* shaderCategoryData = shadersData->FirstChildElement("Category");

        vector<const char*> attributes;
        vector<const char*> uniforms;

        std::stringbuf buffer;      // empty stringbuf
        std::ostream os(&buffer);  // associate stream buffer to stream

        while (shaderCategoryData)
        {
            const char* subFolder = shaderCategoryData->Attribute("name");

            tinyxml2::XMLElement* shaderData = shaderCategoryData->FirstChildElement("Shader");

            while (shaderData)
            {
                const char* shaderName   = shaderData->Attribute("name");
                const char* vertexFile   = shaderData->Attribute("vertex");
                const char* fragmentFile = shaderData->Attribute("fragment");
                const char* geometryFile = shaderData->Attribute("geometry");
                
                if (vertexFile && fragmentFile)
                {
                    buffer.str(std::string()); //Clear the buffer

                    os << globalPath << subFolder << vertexFile << ".vert" << fileExtension;
                    std::string fullVertexPath = buffer.str();

                    buffer.str(std::string()); //Clear the buffer
                    
                    os << globalPath << subFolder << fragmentFile << ".frag" << fileExtension;
                    std::string fullFragmentPath = buffer.str();
                    
                    //Try to find the geometry shader
                    std::string fullGeometryPath = "";
                    if (geometryFile)
                    {
                        buffer.str(std::string()); //Clear the buffer

                        os << globalPath << subFolder << geometryFile << ".geo" << fileExtension;
                        fullGeometryPath = buffer.str();
                    }

                    /*std::cout << shaderName << " ---\"" << fullVertexPath << '"' << std::endl;
                    std::cout << shaderName << " ---\"" << fullFragmentPath << '"' << std::endl;*/
                    
                    LoadShader(shaderName, attributes, uniforms, fullVertexPath.c_str(), fullFragmentPath.c_str(), fullGeometryPath.c_str());
                }

                shaderData = shaderData->NextSiblingElement();
            }
            shaderCategoryData = shaderCategoryData->NextSiblingElement();
        }

        return;
    }
    
    void SymphonyEngine::LoadCommandLineArguments(const char* commandLineFilename)
    {
        if (commandLineFilename == nullptr)
        {
            return;
        }

        std::ifstream in_stream;
        in_stream.open(commandLineFilename);
        string rawLine;

        const char ignoreLineChar = '#';
        while (std::getline(in_stream, rawLine, '\n'))
        {
            //Ignore anything that starts as a comment
            if (rawLine[0] != ignoreLineChar)
            {
                rsize_t lineSize = rawLine.length() + 1;
                char* line = new char[lineSize];
                strcpy_s(line, lineSize, rawLine.c_str());

                //Extract all the possible arguments out of the rawLine
                {
                    char* token;
                    char* next_token = nullptr;
                    const char* separators = "- ";
                    token = strtok_s(line, separators, &next_token);
                    while (token != nullptr)
                    {
                        //TO-DO: Save these!
                        std::cout << token << std::endl;
                        token = strtok_s(nullptr, separators, &next_token);
                    }
                }

                delete[] line;
            }
        }

        in_stream.close();
    }
}