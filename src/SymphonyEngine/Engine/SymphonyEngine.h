#pragma once

#include "../Common.h"

#include "../Utilities/Singleton.h"
#include "../Time/GameTimer.h"
#include "Scene.h"
#include "../Window/Window.h"

namespace Symphony
{
    class SymphonyEngine : public Singleton<SymphonyEngine>
    {
        friend class Singleton<SymphonyEngine>;

    public:
        const char* SymphonyEngine::Version() const;

        bool Initialise();
        void Run();

        void AddScene(Scene* newScene);
        void NextScene();
        void ChangeScene(std::string sceneName);
        void ChangeScene(unsigned int sceneID);
        
    protected:
        bool initialised;
        bool running;
        bool changeSceneFlag;
        GameTimer* gameTimer;
        std::vector<Scene*> scenes;
        Scene* currentScene;
        unsigned int nextSceneID = 0;
        Window* window;

        void LoadNextScene();

    private:
        SymphonyEngine();
        virtual ~SymphonyEngine();
    };
}