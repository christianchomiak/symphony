#include "SymphonyEngine.h"

#include <sstream>
#include <fstream>

#include "../IO/DataReader.h"
#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"
#include "../Rendering/Shader.h"
#include "../Rendering/textures/TextureManager.h"
#include "../Rendering/UI/Font.h"

//#include <imgui/imgui.h>
#include "../UI/imgui/ImGuiManager.h"

namespace Symphony
{
    SymphonyEngine* SymphonyEngine::instance = nullptr;
    const char* SymphonyEngine::version = "Symphony Engine - v0.1.0 \"Bittersweet\"";

    SymphonyEngine::SymphonyEngine()
    {
        currentScene    = nullptr;
        window          = nullptr;
        editor          = nullptr;
        
        running         = true;
        changeSceneFlag = true;
        initialised     = false;
    }

    SymphonyEngine::~SymphonyEngine()
    {
        for (Scene* scene : scenes)
        {
            if (scene)
            {
                delete scene;
            }
        }
        
        if (window)
        {
            delete window;
        }

        if (editor)
        {
            delete editor;
        }
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
        wProperties.title       = "Symphony Engine demo";
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

        LogInfo(SymphonyEngine::version);
        //std::cout << std::endl << SymphonyEngine::version << std::endl << std::endl;
        
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

            editor = new SymphonyEditor();
        }

        return initialised;
    }
    
    void SymphonyEngine::Run()
    {
        if (!initialised)
        {
            LogError("Symphony Engine hasn't been initialised yet");
            return;
        }
        
        ChangeScene(0);
        LoadNextScene();
        
        if (!currentScene)
        {
            LogError("No initial scene was found");
            running = false;
        }
        
        MouseRef    mouse    = InputManager::GetMouse();
        KeyboardRef keyboard = InputManager::GetKeyboard();
        
        //TO-DO: Code regarding FPS check could be enabled/disabled by the user
        double frameStartTime, frameEndTime = 0.0, frameTotalTime;
        std::stringstream ss;

        bool frameStartedWithPausedFrame;
        bool forceFrameExecution;

        bool useImGui = true;

        ImGuiManager imGuiManager;
        
        while (running)
        {
            InputManager::Update();
            window->Update();
            
            frameStartedWithPausedFrame = Time::IsPaused();
            forceFrameExecution = frameStartedWithPausedFrame && keyboard.KeyDown(Key::ARROW_RIGHT);

            Time::paused = frameStartedWithPausedFrame && !forceFrameExecution;

            frameStartTime = Time::Update();

            ////////////

            if (InputManager::InputIsBlocked())
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
            
            //TO-DO: Should this be split in two functions, one at the start and
            //       the other at the end of the frame?
            editor->Update(currentScene);

            if (changeSceneFlag)
            {
                LoadNextScene();
            }

            if (currentScene)
            {
                currentScene->Update();
                currentScene->Render();
            }
            
            imGuiManager.Render(window->WindowWidth(),      window->WindowHeight(),
                                window->FrameBufferWidth(), window->FrameBufferHeight());

            window->SwapBuffers();

            ////////////

            frameEndTime   = Time::GetCurrentTime();
            frameTotalTime = frameEndTime - frameStartTime;
            
            if (!frameStartedWithPausedFrame || forceFrameExecution)
            {
                ++Time::frame;
            }
            
            //Assert(!keyboard.KeyDown(Key::E), "Symphony Engine", "Resource not available\nDo you want to try again?");

            //If we skipped the frame, we may have changed its paused status assuming a different scenario
            /*if (frameStartedWithPausedFrame && forceFrameExecution && frameStartedWithPausedFrame != Time::paused)
            {
                Time::paused = !Time::paused;
            }*/

            //This represents the above without the need of any branching
            //bool requiresFix = frameStartedWithPausedFrame && forceFrameExecution && frameStartedWithPausedFrame != Time::paused;
            
            //This simplifies even more the above statement
            //bool requiresFix = forceFrameExecution && !Time::paused;
            //Time::paused = (!requiresFix && Time::paused) || (requiresFix && !Time::paused);

            //Time::paused = ((!forceFrameExecution || Time::paused) && Time::paused) || (forceFrameExecution && !Time::paused);
            Time::paused |= forceFrameExecution;
            
            //Do we want to start next frame paused?
            /*if (keyboard.KeyDown(Key::SPACE))
            {
                Time::paused = !Time::paused;
            }*/
            
            //Ain't nobody got time to waste time branching on an if-statement, let's XOR it
            //Time::paused = (!Time::paused && keyboard.KeyDown(Key::SPACE)) || (Time::paused  && !keyboard.KeyDown(Key::SPACE));
            //Time::paused XOR keyboard.KeyDown(Key::SPACE)
            Time::paused ^= keyboard.KeyDown(Key::SPACE);

            running &= !window->Closed() && !keyboard.KeyDown(Key::ESC);
        }

        imGuiManager.Shutdown();
        Unload();

        Log("Symphony Engine has now finished execution");
    }

    void SymphonyEngine::AddScene(Scene* newScene)
    {
        Assert(newScene, "Trying to add a null scene to the engine");

        if (newScene)
        {
            newScene->SetID(scenes.size());
            scenes.push_back(newScene);
            return;
        }
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
        
        Assert(newScene, "Trying to change into an inexistent scene");

        if (newScene)
        {
            ChangeScene(newScene->GetID());
        }
    }

    void SymphonyEngine::ChangeScene(unsigned int newSceneID)
    {
        if (scenes.size() == 0)
        {
            LogError("No scenes are registered in the engine");
            return;
        }
        else if (newSceneID >= scenes.size())
        {
            LogErrorF("Error trying to load scene #%d, only %d scene(s) exist", newSceneID, scenes.size());
            return;
        }
        nextSceneID     = newSceneID;
        changeSceneFlag = true;
    }
    
    void SymphonyEngine::LoadShader(HashString shaderName,
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
            LogError("No filename was specified, cannot load any shaders");
            return;
        }
        
        tinyxml2::XMLDocument shadersFile;

        if (!ValidateXmlLoading(filename, shadersFile.LoadFile(filename)))
        {
            LogError("Cannot load any shaders");
            return;
        }

        //tinyxml2::XMLElement* shadersData = doc.FirstChildElement("SymphonyShaders")->FirstChildElement("WindowData");
        
        tinyxml2::XMLElement* root = shadersFile.FirstChildElement("SymphonyShaders");

        if (!root)
        {
            LogErrorF("Could not find the root SymphonyShaders property in \"%s\". Aborting.", filename);
            return;
        }

        //Check if a global path to the shaders was specified
        const char* globalPath = GetTextFromXmlElement(root, "DefaultPath");
        
        tinyxml2::XMLElement* shadersData = root->FirstChildElement("Shaders");

        if (!shadersData)
        {
            LogErrorF("Could not find any shader data in \"%s\". Aborting.", filename);
            return;
        }

        const char* fileExtension = GetTextFromXmlElement(root, "FileExtension");

        if (!fileExtension)
        {
            LogErrorF("Could not find any file extension specified in \"%s\". Aborting.", filename);
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

        LogInfo("**Command line arguments **");
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
                        LogF("%s", token);
                        token = strtok_s(nullptr, separators, &next_token);
                    }
                }

                delete[] line;
            }
        }
        LogInfo("**End of command line arguments **");

        in_stream.close();
    }
}