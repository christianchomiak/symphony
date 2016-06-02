#include "SymphonyEngine.h"

#include <sstream>
#include "../Debugging/Debugging.h"

namespace Symphony
{
    SymphonyEngine::SymphonyEngine()
    {
        gameTimer = GameTimer::CreateTimer();
        currentScene = nullptr;
        running = true;
    }

    SymphonyEngine::~SymphonyEngine()
    {
        for (Scene* s : scenes)
        {
            delete s;
        }
        delete gameTimer;
    }
    
    void SymphonyEngine::PrintInfo()
    {
        std::cout << std::endl << "Symphony Engine - v0.1.0 \"Bittersweet\"" << std::endl << std::endl;
    }

    bool SymphonyEngine::Initialise()
    {
        std::cout.setf(std::ios::boolalpha);
        return true;
    }

    void SymphonyEngine::Run()
    {
        PrintInfo();

        float deltaTime;

        //TO-DO: Code regarding FPS check could be enabled/disabled by the user
        int numberOfFrames = 0;
        float frameStartTime, frameEndTime = 0.0f, frameTotalTime;
        float nextTimeLap = frameEndTime + 1.0f;
        std::stringstream ss;
        
        ChangeScene(1);

        if (!currentScene)
        {
            Debug::LogError("No initial scene was found");
            running = false;
        }

        while (running)
        {
            if (changeSceneFlag)
            {
                LoadNextScene();
            }

            gameTimer->Update();
            deltaTime = gameTimer->GetDeltaTime();

            //frameStartTime = gameTimer->GetMS();
            
            if (currentScene) currentScene->Update(deltaTime);
            Debug::Log("");
            _WATCHPOINT
            running = false;
            
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
        }
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
}