#pragma once

//#include "../Utilities/Singleton.h"

#ifdef _DEBUG

#include <iostream>

//#   include "../Macros/PlatformMacros.h"
#   include "../Macros/ClassMacros.h"

#   define _WATCHPOINT Debug::DoWatchpoint(__FILE__, __LINE__, __FUNCTION__);

#   define LogF(format, ...)        Debug::DoLogF(format, __VA_ARGS__)
#   define LogInfoF(format, ...)    Debug::DoLogInfoF(format, __VA_ARGS__)
#   define LogWarningF(format, ...) Debug::DoLogWarningF(format, __VA_ARGS__)
#   define LogErrorF(format, ...)   Debug::DoLogErrorF(format, __VA_ARGS__)

#   define Log(message)         Debug::DoLog(message)
#   define LogInfo(message)     Debug::DoLogInfo(message)
#   define LogWarning(message)  Debug::DoLogWarning(message)
#   define LogError(message)    Debug::DoLogError(message)

#   define Assert(condition, message)\
    if ( Debug::DoAssertTest((condition), "Symphony Engine", (message)) == Debug::AssertUserResponse::ASSERT_PAUSE )\
    {\
        __debugbreak();\
    }

#   define AssertF(condition, msgBodyFormat, ...)\
    if ( Debug::DoAssertTestWithFormat((condition), "Symphony Engine", (msgBodyFormat), ##__VA_ARGS__) == Debug::AssertUserResponse::ASSERT_PAUSE )\
    {\
        __debugbreak();\
    }

namespace Symphony
{
    class Debug //: public Singleton<Debug>
    {
        SINGLETON(Debug)

        //friend class Singleton<Debug>;
    public:
        enum class AssertUserResponse
        {
            ASSERT_PAUSE,
            ASSERT_IGNORE
        };

        static void DoLogF(const char* format, ...);
        static void DoLogInfoF(const char* format, ...);
        static void DoLogWarningF(const char* format, ...);
        static void DoLogErrorF(const char* format, ...);

        static void DoLog(const char* message);
        static void DoLogInfo(const char* message);
        static void DoLogWarning(const char* message);
        static void DoLogError(const char* message);

        static void DoLog(const std::string& message);
        static void DoLogInfo(const std::string& message);
        static void DoLogWarning(const std::string& message);
        static void DoLogError(const std::string& message);

        static void DoWatchpoint(const char* file, int line, const char* function);

        static Debug::AssertUserResponse DoAssertTest(bool condition, const char* msgTitle, const char* msgBody);
        static Debug::AssertUserResponse DoAssertTestWithFormat(bool condition, const char* msgTitle, const char* msgBodyFormat, ...);

    protected:
        static const size_t MESSAGE_BUFFER_SIZE = 1024; //TO-DO: Is this enough or too much for a log entry?
        static const int LOG_COLOR      = 7;    //WHITE
        static const int INFO_COLOR     = 3;    //LIGHT BLUE
        static const int WARNING_COLOR  = 14;   //LIGHT YELLOW
        static const int ERROR_COLOR    = 12;   //LIGHT RED

        void InternalLog(const char* message);
        void InternalLogInfo(const char* message);
        void InternalLogWarning(const char* message);
        void InternalLogError(const char* message);
    };
}


inline void Symphony::Debug::DoLog(const char* message)
{
    Instance()->InternalLog(message);
}

inline void Symphony::Debug::DoLog(const std::string& message)
{
    Instance()->InternalLog(message.c_str());
}

inline void Symphony::Debug::DoLogInfo(const char* message)
{
    Instance()->InternalLogInfo(message);
}

inline void Symphony::Debug::DoLogInfo(const std::string& message)
{
    Instance()->InternalLogInfo(message.c_str());
}

inline void Symphony::Debug::DoLogWarning(const char* message)
{
    Instance()->InternalLogWarning(message);
}

inline void Symphony::Debug::DoLogWarning(const std::string& message)
{
    Instance()->InternalLogWarning(message.c_str());
}

inline void Symphony::Debug::DoLogError(const char* message)
{
    Instance()->InternalLogError(message);
}

inline void Symphony::Debug::DoLogError(const std::string& message)
{
    Instance()->InternalLogError(message.c_str());
}

inline void Symphony::Debug::DoWatchpoint(const char* file, int line, const char* function)
{
    const char *szFile = file; // __FILE__;
    int iLine          = line;
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
}

#else

#   define _WATCHPOINT

#   define LogF(format, ...)
#   define LogInfoF(format, ...)
#   define LogWarningF(format, ...)
#   define LogErrorF(format, ...)

#   define Log(message)
#   define LogInfo(message)
#   define LogWarning(message)
#   define LogError(message)

#   define Assert(condition, message)
#   define AssertF(condition, msgBodyFormat, ...)

#endif