#pragma once

#include "../Utilities/Singleton.h"

#include <iostream>

#ifdef _DEBUG
#   define _WATCHPOINT Debug::Watchpoint(__FILE__, __LINE__, __FUNCTION__);
#else
#   define _WATCHPOINT
#endif

#include "../Macros/PlatformMacros.h"

namespace Symphony
{
    class Debug : public Singleton<Debug>
    {
        friend class Singleton<Debug>;
    public:
        static void LogF(const char* format, ...);
        static void LogWarningF(const char* format, ...);
        static void LogErrorF(const char* format, ...);

        static void Log(const char* message);
        static void LogWarning(const char* message);
        static void LogError(const char* message);
        
        static void Log(const std::string& message);
        static void LogWarning(const std::string& message);
        static void LogError(const std::string& message);
        
        static void Watchpoint(const char* file, int line, const char* function);

    protected:
        static const size_t MESSAGE_BUFFER_SIZE = 1024; //TO-DO: Is this enough or too much for a log entry?
        static const int LOG_COLOR      = 7;  //WHITE
        static const int WARNING_COLOR  = 14; //LIGHT YELLOW
        static const int ERROR_COLOR    = 12; //LIGHT RED

        void InternalLog(const char* message);
        void InternalLogWarning(const char* message);
        void InternalLogError(const char* message);
        
        void InternalWatchpoint(const char* file, int line, const char* function);
    };
}


inline void Symphony::Debug::Log(const char* message)
{
    DEBUG_ONLY(Instance()->InternalLog(message));
}
inline void Symphony::Debug::Log(const std::string& message)
{
    DEBUG_ONLY(Instance()->InternalLog(message.c_str()));
}

inline void Symphony::Debug::LogWarning(const char* message)
{
    DEBUG_ONLY(Instance()->InternalLogWarning(message));
}
inline void Symphony::Debug::LogWarning(const std::string& message)
{
    DEBUG_ONLY(Instance()->InternalLogWarning(message.c_str()));
}

inline void Symphony::Debug::LogError(const char* message)
{
    DEBUG_ONLY(Instance()->InternalLogError(message));
}
inline void Symphony::Debug::LogError(const std::string& message)
{
    DEBUG_ONLY(Instance()->InternalLogError(message.c_str()));
}