#pragma comment(lib, "SymphonyEngine.lib")

#if !defined(_DEBUG) && defined(_WIN32)
#   include <windows.h>
#endif

//#include <memory> //This is for unique_ptr and shared_ptr

#include "../SymphonyEngine/Engine/SymphonyEngine.h"
#include "../SymphonyEngine/Utilities/HashString.h"
#include "TestScene.h"

/* #include <algorithm>
#include <stdlib.h>
#include <time.h> */

using namespace std;
using namespace Symphony;

SymphonyEngine* sEngine = nullptr;

void TestGround()
{
    std::cout.setf(std::ios::boolalpha);
    
    /*HashString hs1 = "Test";
    std::string s1 = "Test";
    const char* s2 = "Test";
    hs1 = s2;
    std::cout << "HS1 == HS2: " << (hs1 == s2) << std::endl;*/
    
    /*srand(time(NULL));
    const int SIZE = 10000;
    int intArray[SIZE];

    for (size_t i = 0; i < SIZE; i++)
    {
        intArray[i] = rand() % 10000;
    }

    StopWatch watch;
    watch.Start();

    std::sort(intArray, intArray + SIZE);

    watch.Stop();

    LogF("Duration: %f", watch.GetElapsedTime());*/
}

#ifdef _DEBUG
int main(int argc, char* args[])
#elif  _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
    sEngine = SymphonyEngine::Instance();
    
    const char* xmlConfig = RESOURCES_FOLDER(SymphonyConfig.xml);

#ifdef _DEBUG
    const char* commandLineArgs = (args == nullptr || argc < 2) ? nullptr : args[1];
#else
    const char* commandLineArgs = nullptr;
#endif
    
    if (!sEngine->Initialise(xmlConfig, commandLineArgs))
    {
        Assert(false, "Error trying to initialise Symphony Engine");
        return -1;
    }
    
    sEngine->AddScene(new TestScene());
    sEngine->Run();
    sEngine->Shutdown();
    
    TestGround();

    DEBUG_ONLY(system("pause");)

    return 0;
}