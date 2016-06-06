#include "SymphonyEngine.h"

#include <sstream>
#include "../Debugging/Debugging.h"
#include "../Input/InputManager.h"
#include "../Rendering/Shader.h"
#include "../Rendering/TextureManager.h"

namespace Symphony
{
    SymphonyEngine* SymphonyEngine::instance = nullptr;
    
    SymphonyEngine::SymphonyEngine()
    {
        currentScene = nullptr;
        window = nullptr;
        running = true;
        initialised = false;
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
    
    const char* SymphonyEngine::Version() const
    {
        return "Symphony Engine - v0.1.0 \"Bittersweet\"";
    }

    bool SymphonyEngine::Initialise()
    {
        Window::WindowProperties wProperties = Window::WindowProperties();
        /*wProperties.cursorMode = Window::CursorMode::NORMAL;
        wProperties.decorated = true;
        wProperties.fullscreen = false;
        wProperties.width = 800;
        wProperties.height = 600;
        wProperties.maximised = false;
        wProperties.resizeable = true;
        wProperties.title = "Symphony Engine demo";
        wProperties.switchableToOtherModes = false;*/

        return Initialise(wProperties);
    }

    bool SymphonyEngine::Initialise(Window::WindowProperties& windowProperties)
    {
        std::cout.setf(std::ios::boolalpha);
        
        std::cout << std::endl << Version() << std::endl << std::endl;
        
        //window = new Window(Version(), 800, 600, true, true, true, false);
        //window = Window::CreateFullScreenWindow(Version(), 1920, 1080, false);
        window = new Window(windowProperties);
        
        initialised = window->Initialise();

        if (!initialised)
        {
            delete window;
            window = nullptr;
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
        
        Keyboard* keyboard = InputManager::GetKeyboard();
        Mouse* mouse = InputManager::GetMouse();
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
            window->SetTitle(std::to_string(deltaTime).c_str());
            
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
            running &= !window->Closed() && !keyboard->KeyDown(Keyboard::KEY_ESC);
        }

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

        Debug::LogWarning("Trying to add a null scene to the engine");
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
            Debug::LogError("Scene \"" + sceneName + "\" doesn't exist");
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
            Debug::LogError("Error trying to load scene #" + std::to_string(newSceneID) +
                            ", only " + std::to_string(scenes.size()) + " scene(s) exist");
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
}