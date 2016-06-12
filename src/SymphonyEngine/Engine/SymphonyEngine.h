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

        bool Initialise();
        bool Initialise(Window::WindowProperties& windowProperties);
        void Run();

        void AddScene(Scene* newScene);
        void NextScene();
        void ChangeScene(string sceneName);
        void ChangeScene(unsigned int sceneID);
        
        //TO-DO: Perhaps this could be done via a text file?
        void LoadShader(const char* shaderName, const vector<const char*>& attributes, const vector<const char*>& uniforms,
                        const char* vertexShaderFilename, const char* fragmentShaderFilename,
                        const char* geometryShaderFilename = nullptr) const;

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