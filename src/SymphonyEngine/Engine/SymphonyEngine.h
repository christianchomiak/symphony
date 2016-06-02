#pragma once

#include "../Utilities/Singleton.h"
#include "../Time/GameTimer.h"
#include "Scene.h"

namespace Symphony
{
    class SymphonyEngine : public Singleton<SymphonyEngine>
    {
        friend class Singleton<SymphonyEngine>;

    public:
        void PrintInfo();

        bool Initialise();
        void Run();

        void AddScene(Scene* newScene);
        void NextScene();
        void ChangeScene(std::string sceneName);
        void ChangeScene(unsigned int sceneID);
        
    protected:
        bool running = true;
        GameTimer* gameTimer;
        std::vector<Scene*> scenes;
        Scene* currentScene;
        unsigned int nextSceneID = 0;
        bool changeSceneFlag = false;

        void LoadNextScene();

    private:
        SymphonyEngine();
        virtual ~SymphonyEngine();
    };
}