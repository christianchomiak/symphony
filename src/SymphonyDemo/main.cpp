#include "../SymphonyEngine/Engine/SymphonyEngine.h"

#pragma comment(lib, "SymphonyEngine.lib")

#include <iostream>

using namespace Symphony;

int main(int argc, char* args[])
{
    std::cout.setf(std::ios::boolalpha);
    
    SymphonyEngine* sEngine = SymphonyEngine::Instance();
    sEngine->Run();
    sEngine->Release();

    system("pause");
}