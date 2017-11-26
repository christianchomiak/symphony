#pragma once

#include <Common.h>

#include <Time/Time.h>
#include <Scene/Scene.h>
#include <Window/Window.h>
#include <Macros/ResourcesMacros.h>
#include <Tools/SymphonyEditor.h>
#include <Utilities/HashString.h>

using namespace std;

namespace Symphony
{
    class SymphonyEngine
    {
    public:
        static const char* version;

        /*
        SUMMARY:
        \\ Setups the engine with default window values
        PARAMS:
        \\ None
        RETURNS:
        \\ Whether the engine initialised correctly
        */
        bool Initialise(const char* commandLineFilename);
        
        /*
        SUMMARY:
        \\ Setups the engine with custom window values defined in a file
        PARAMS:
        \\ filename: name of the file containing the properties
        RETURNS:
        \\ Whether the engine initialised correctly
        */
        bool Initialise(const char* configFilename, const char* commandLineFilename);
        
        void NextScene();
        void AddScene(Scene* newScene);
        void ChangeScene(const HashString& desiredScene);
        void ChangeScene(uint desiredSceneIndex);
        uint GetCurrentSceneIndex() const;
        
        void LoadShaders(const char* shadersFilename);

        void Run();

        static inline SymphonyEngine* Instance()
        {
            if (!instance) instance = new SymphonyEngine();
            return instance;
        }

        static inline void Shutdown()
        {
            if (instance)
            {
                delete instance;
                instance = nullptr;
            }
        }

    protected:
        bool initialised;
        bool running;
        bool changeSceneFlag;
        vector<Scene*> scenes;
        Scene* currentScene;
        size_t nextSceneIndex;
        Window* window;
        SymphonyEditor* editor;

        void LoadNextScene();
        void Unload();
        
        void LoadCommandLineArguments(const char* commandLineFilename);

        /*
        SUMMARY:
        \\ Setups the engine with custom window values
        PARAMS:
        \\ windowProperties: custom initial values for the window
        RETURNS:
        \\ Whether the engine initialised correctly
        */
        bool Initialise(const Window::WindowProperties& windowProperties, const char* commandLineFilename);

        
        void LoadShader(HashString shaderName, const char* vertexShaderFilename,
                        const char* fragmentShaderFilename, const char* geometryShaderFilename = nullptr) const;

    private:
        static SymphonyEngine* instance;
        SymphonyEngine();
        SymphonyEngine(SymphonyEngine&) = delete;
        ~SymphonyEngine();
    };
}