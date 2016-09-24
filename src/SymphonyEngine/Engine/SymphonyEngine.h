#pragma once

#include "../Common.h"

#include "../Utilities/Singleton.h"
#include "../Time/Time.h"
#include "../Scene/Scene.h"
#include "../Window/Window.h"

using namespace std;

namespace Symphony
{
    class SymphonyEngine
    {
    public:
        const char* SymphonyEngine::Version() const;

        /*
        SUMMARY:
        \\ Setups the engine with default window values
        PARAMS:
        \\ None
        RETURNS:
        \\ Whether the engine initialised correctly
        */
        bool Initialise();

        //TO-DO: Should this receive a const& instead of &?
        /*
        SUMMARY:
            \\ Setups the engine with custom window values
        PARAMS:
            \\ windowProperties: custom initial values for the window
        RETURNS:
            \\ Whether the engine initialised correctly
        */
        bool Initialise(Window::WindowProperties& windowProperties);

        /*
        SUMMARY:
        \\ Setups the engine with custom window values defined in a file
        PARAMS:
        \\ filename: name of the file containing the properties
        RETURNS:
        \\ Whether the engine initialised correctly
        */
        bool Initialise(const char* filename);
        
        void NextScene();
        void AddScene(Scene* newScene);
        void ChangeScene(string sceneName);
        void ChangeScene(unsigned int sceneID);
        
        //TO-DO: Perhaps this could be done via a text file?
        void LoadShader(const char* shaderName, const vector<const char*>& attributes, const vector<const char*>& uniforms,
                        const char* vertexShaderFilename, const char* fragmentShaderFilename,
                        const char* geometryShaderFilename = nullptr) const;

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

    private:
        static SymphonyEngine* instance;
        SymphonyEngine();
        SymphonyEngine(SymphonyEngine&) = delete;
        ~SymphonyEngine();
    };
}