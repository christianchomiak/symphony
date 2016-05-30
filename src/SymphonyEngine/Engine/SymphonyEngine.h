#pragma once

#include <iostream>

#include "../Utilities/Singleton.h"
#include "../Time/GameTimer.h"
#include "Scene.h"

namespace Symphony
{
    class SymphonyEngine : public Singleton<SymphonyEngine>
    {
        friend class Singleton<SymphonyEngine>;

    public:
        inline void PrintInfo()
        {
            std::cout << "Symphony Engine - v0.1.0 \"Bittersweet\"" << std::endl;
        }

        void Run();

    protected:
        bool running = true;
        GameTimer* gameTimer;
        Scene* currentScene;
        
    private:
        SymphonyEngine();
        virtual ~SymphonyEngine();
    };
}