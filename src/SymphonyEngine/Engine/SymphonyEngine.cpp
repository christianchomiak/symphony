#include "SymphonyEngine.h"

#include <sstream>
#include <fstream>

#include "../IO/DataReader.h"
#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"
#include "../Rendering/Shader.h"
#include "../Rendering/textures/TextureManager.h"
#include "../Rendering/UI/Font.h"

#include <imgui/imgui.h>
#include "../UI/imgui/ImGuiManager.h"

namespace Symphony
{
    SymphonyEngine* SymphonyEngine::instance = nullptr;
    const char* SymphonyEngine::version = "Symphony Engine - v0.1.0 \"Bittersweet\"";

    SymphonyEngine::SymphonyEngine()
    {
        currentScene    = nullptr;
        window          = nullptr;
        running         = true;
        changeSceneFlag = true;
        initialised     = false;
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
        
        initialised &= Font::LoaderWorks();

        if (initialised)
        {
            Font::Load("Arial", RESOURCES_FOLDER(Fonts/arial.ttf));

            LoadShaders(RESOURCES_FOLDER(shaders.xml));
        }

        return initialised;
    }
    
    void SymphonyEngine::Run()
    {
        if (!initialised)
        {
            Debug::LogError("Symphony Engine hasn't been initialised yet");
            return;
        }
        
        ChangeScene(0);
        LoadNextScene();
        
        if (!currentScene)
        {
            Debug::LogError("No initial scene was found");
            running = false;
        }
        
        MouseRef mouse       = InputManager::GetMouse();
        KeyboardRef keyboard = InputManager::GetKeyboard();


        //TO-DO: Code regarding FPS check could be enabled/disabled by the user
        double frameStartTime, frameEndTime = 0.0, frameTotalTime;
        unsigned long long frame = 0;
        unsigned long long targetFrame = 0;
        std::stringstream ss;

        bool paused = false;
        bool skipPauseThisFrame = false;

        bool useImGui = true;

        ImGuiManager imGuiManager;

        while (running)
        {
            InputManager::Update();
            window->Update();

            if (keyboard.KeyDown(Key::SPACE))
            {
                //window->ChangeMode();
                paused = !paused;
            }

            skipPauseThisFrame = keyboard.KeyDown(Key::ARROW_RIGHT);
            
            Time::paused = paused && !skipPauseThisFrame;
            
            ////////////

            frameStartTime = Time::Update();
            
            if (InputManager::inputBlockedInGame)
            {
                window->ChangeCursorMode(imGuiManager.IsImGuiDrawingCursor()
                    ? Window::CursorMode::HIDDEN
                    : Window::CursorMode::VISIBLE);
            }
            else
            {
                window->ChangeCursorMode(imGuiManager.IsImGuiDrawingCursor()
                    ? Window::CursorMode::HIDDEN
                    : window->GetDefaultProperties().cursorMode);
            }

            imGuiManager.PrepareForNewFrame(Time::TrueDeltaTime(),
                window->IsFocused(),
                window->WindowWidth(), window->WindowHeight(),
                window->FrameBufferWidth(), window->FrameBufferHeight());

            ////////////
            
            if (changeSceneFlag)
            {
                LoadNextScene();
            }

            if (currentScene)
            {
                currentScene->Update();
                currentScene->Render();
            }
            
            imGuiManager.Render(window->WindowWidth(), window->WindowHeight(),
                window->FrameBufferWidth(), window->FrameBufferHeight());

            frameEndTime = Time::GetCurrentTime();
            frameTotalTime = frameEndTime - frameStartTime;
            if (!Time::paused)
            {
                /*if (frame <= targetFrame)
                {
                    ss.clear();
                    ss.str("FPS: ");
                    ss << "FPS: " << (1.0 / frameTotalTime)
                       << " | ms/frame: "  << frameTotalTime
                       << " | deltaTime: " << deltaTime
                       << " | frame: "     << frame;
                    window->SetTitle(ss.str().c_str());

                    //Currently we need to do this every frame
                    //if we want to print the frame data in the window title
                    targetFrame = frame + 1;
                }*/

                ++frame;
            }
            
            window->SwapBuffers();
            running &= !window->Closed() && !keyboard.KeyDown(Key::ESC);
        }

        imGuiManager.Shutdown();
        Unload();

        Debug::Log("Symphony Engine has now finished execution");
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
                                    const char* vertexShaderFilename, const char* fragmentShaderFilename,
                                    const char* geometryShaderFilename) const
    {
        Shader::CreateNewShader(shaderName, vertexShaderFilename, fragmentShaderFilename, geometryShaderFilename);
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
        Font::UnloadAll();
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
                    
                    LoadShader(shaderName, fullVertexPath.c_str(), fullFragmentPath.c_str(), fullGeometryPath.c_str());
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