#include "Debugging.h"

#include <string>
#include <cstdarg>


//TO-DO: Should _WIN32 be wrapped somewhere?
#if _WIN32
#   include <windows.h>   // WinApi header
#   define SET_TERMINAL_TEXT_COLOR(color) \
        { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
        if (hConsole != nullptr) SetConsoleTextAttribute(hConsole, color); }
#else
#   define SET_TERMINAL_TEXT_COLOR(color)
#endif


void Symphony::Debug::LogF(const char* format, ...)
{
#ifdef _DEBUG
    va_list arg;
    char buffer[MESSAGE_BUFFER_SIZE];
    va_start(arg, format);
    int ret = vsprintf_s(buffer, format, arg);
    va_end(arg);

    Instance()->InternalLog(buffer);
#endif
}

void Symphony::Debug::LogWarningF(const char* format, ...)
{
#ifdef _DEBUG
    va_list arg;
    char buffer[MESSAGE_BUFFER_SIZE];
    va_start(arg, format);
    int ret = vsprintf_s(buffer, format, arg);
    va_end(arg);

    Instance()->InternalLogWarning(buffer);
#endif
}

void Symphony::Debug::LogErrorF(const char* format, ...)
{
#ifdef _DEBUG
    va_list arg;
    char buffer[MESSAGE_BUFFER_SIZE];
    va_start(arg, format);
    int ret = vsprintf_s(buffer, format, arg);
    va_end(arg);

    Instance()->InternalLogError(buffer);
#endif
}



void Symphony::Debug::InternalLog(const char* message)
{
    //SET_TERMINAL_TEXT_COLOR(7);
    //log.push_back(message);
    std::cout << message << std::endl;
}

void Symphony::Debug::InternalLogWarning(const char* message)
{
    SET_TERMINAL_TEXT_COLOR(WARNING_COLOR);
    //warningLog.push_back(message);
    std::cout << message << std::endl;
    SET_TERMINAL_TEXT_COLOR(LOG_COLOR);
}

void Symphony::Debug::InternalLogError(const char* message)
{
    SET_TERMINAL_TEXT_COLOR(ERROR_COLOR);
    //errorLog.push_back(message);
    std::cout << message << std::endl;
    SET_TERMINAL_TEXT_COLOR(LOG_COLOR);
}



void Symphony::Debug::Watchpoint(const char* file, int line, const char* function)
{
    DEBUG_ONLY(Instance()->InternalWatchpoint(file, line, function));
}

void Symphony::Debug::InternalWatchpoint(const char* file, int line, const char* function)
{
#ifdef _DEBUG
    const char *szFile = file; // __FILE__;
    int iLine = line;
    const char *szFunc = function; // __FUNCTION__; // Func name
    const char *szFunD = __FUNCDNAME__; // Decorated
    const char *szFunS = __FUNCSIG__; // Signature

    printf("[BREAKPOINT]\n");
    printf("File: %s\n", szFile);
    printf("Line: %d\n", iLine);
    printf("Function: %s\n", szFunc);
    printf("[/BREAKPOINT]\n");
    /*printf("Function (dec): %s\n", szFunD);
    printf("Function (sig): %s\n", szFunS);*/
#endif
}