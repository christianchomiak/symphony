#pragma once

#include "../Common.h"

#include "../Time/Time.h"
#include "../Scene/Scene.h"
#include "../Window/Window.h"

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
        void ChangeScene(string sceneName);
        void ChangeScene(unsigned int sceneID);
        
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
        unsigned int nextSceneID = 0;
        Window* window;

        void LoadNextScene();
        void Unload();
        void LoadFonts();
        
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

        
        void LoadShader(const char* shaderName, const vector<const char*>& attributes, const vector<const char*>& uniforms,
            const char* vertexShaderFilename, const char* fragmentShaderFilename,
            const char* geometryShaderFilename = nullptr) const;

    private:
        static SymphonyEngine* instance;
        SymphonyEngine();
        SymphonyEngine(SymphonyEngine&) = delete;
        ~SymphonyEngine();
    };
}