#pragma once

#include "../Common.h"

#include "../Utilities/Singleton.h"
#include "../Time/Time.h"
#include "Scene.h"
#include "../Window/Window.h"

namespace Symphony
{
    class SymphonyEngine
    {
    public:
        const char* SymphonyEngine::Version() const;

        bool Initialise();
        void Run();

        void AddScene(Scene* newScene);
        void NextScene();
        void ChangeScene(std::string sceneName);
        void ChangeScene(unsigned int sceneID);
        
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
        std::vector<Scene*> scenes;
        Scene* currentScene;
        unsigned int nextSceneID = 0;
        Window* window;

        void LoadNextScene();

    private:
        static SymphonyEngine* instance;
        SymphonyEngine();
        SymphonyEngine(SymphonyEngine&) = delete;
        ~SymphonyEngine();
    };
}