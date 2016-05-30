#include "SymphonyEngine.h"

#include <sstream>
#include "../Debugging/Debugging.h"

namespace Symphony
{
    SymphonyEngine::SymphonyEngine()
    {
        gameTimer = GameTimer::CreateTimer();
        currentScene = new Scene();
    }

    SymphonyEngine::~SymphonyEngine()
    {
        delete gameTimer;
        delete currentScene;
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
        
        if (currentScene) currentScene->Initialise();

        while (running)
        {
            gameTimer->Update();
            deltaTime = gameTimer->GetDeltaTime();

            //frameStartTime = gameTimer->GetMS();
            
            if (currentScene) currentScene->Update(deltaTime);
            Debug::Log("");
            _WATCHPOINT;
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
}