#pragma comment(lib, "SymphonyEngine.lib")

//#include <memory> //This is for unique_ptr and shared_ptr

#include "../SymphonyEngine/Engine/SymphonyEngine.h"
#include "../SymphonyEngine/Utilities/HashString.h"
#include "TestScene.h"

using namespace std;
using namespace Symphony;

SymphonyEngine* sEngine = nullptr;

void TestGround()
{
    std::cout.setf(std::ios::boolalpha);

    HashString hs1 = "Test";
    std::string s1 = "Test";
    const char* s2 = "Test";
    hs1 = s2;
    std::cout << "HS1 == HS2: " << (hs1 == s2) << std::endl;
}

int main(int argc, char* args[])
{
    sEngine = SymphonyEngine::Instance();
    
    const char* xmlConfig = RESOURCES_FOLDER(SymphonyConfig.xml);
    const char* commandLineArgs = (args == nullptr || argc < 2) ? nullptr : args[1];

    if (!sEngine->Initialise(xmlConfig, commandLineArgs))
    {
        std::cerr << "Error trying to initialise Symphony Engine" << std::endl;
        system("pause");
        return -1;
    }
    
    sEngine->AddScene(new TestScene());
    sEngine->Run();
    sEngine->Shutdown();
    
    system("pause");

    return 0;
}