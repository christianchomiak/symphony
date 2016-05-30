#include "Debugging.h"

#include <string>

void Symphony::Debug::Log(std::string message)
{
    Instance()->InternalLog(message);
}

void Symphony::Debug::LogWarning(std::string message)
{
    Instance()->InternalLogWarning(message);
}

void Symphony::Debug::LogError(std::string message)
{
    Instance()->InternalLogError(message);
}

void Symphony::Debug::Watchpoint(const char* file, int line, const char* function)
{
    Instance()->InternalWatchpoint(file, line, function);
}

void Symphony::Debug::InternalLog(std::string message)
{
    //log.push_back(message);
    std::cout << message << std::endl;
}

void Symphony::Debug::InternalLogWarning(std::string message)
{
    //warningLog.push_back(message);
    std::cout << message << std::endl;
}

void Symphony::Debug::InternalLogError(std::string message)
{
    //errorLog.push_back(message);
    std::cout << message << std::endl;
}

void Symphony::Debug::InternalWatchpoint(const char* file, int line, const char* function)
{
    const char *szFile = file; // __FILE__;
    int iLine = line;
    const char *szFunc = function; // __FUNCTION__; // Func name
    const char *szFunD = __FUNCDNAME__; // Decorated
    const char *szFunS = __FUNCSIG__; // Signature

    printf("File: %s\n", szFile);
    printf("Line: %d\n", iLine);
    printf("Function: %s\n", szFunc);
    /*printf("Function (dec): %s\n", szFunD);
    printf("Function (sig): %s\n", szFunS);*/
}
