#pragma comment(lib, "SymphonyEngine.lib")

#include <iostream>

#include "../SymphonyEngine/Engine/SymphonyEngine.h"

#include "TestScene.h"

using namespace Symphony;

int main(int argc, char* args[])
{
    SymphonyEngine* sEngine = SymphonyEngine::Instance();
    
    if (!sEngine->Initialise())
    {
        std::cout << "Error trying to initialise Symphony Engine" << std::endl;
        system("pause");
        return -1;
    }

    //std::cout << glGetString(GL_VERSION) << std::endl;
    sEngine->AddScene(new TestScene());
    sEngine->Run();
    sEngine->Shutdown();
    
    system("pause");
    
    return 0;
}