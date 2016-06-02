#pragma comment(lib, "SymphonyEngine.lib")

#include "../SymphonyEngine/Engine/SymphonyEngine.h"

#include "TestScene.h"

#include <iostream>

using namespace Symphony;

int main(int argc, char* args[])
{    
    SymphonyEngine* sEngine = SymphonyEngine::Instance();
    
    if (!sEngine->Initialise())
    {
        std::cout << "Error trying to initialise Symphony Engine" << std::endl;
        return -1;
    }

    sEngine->AddScene(new TestScene());
    sEngine->Run();
    sEngine->Release();

    system("pause");

    return 0;
}