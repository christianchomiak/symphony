#pragma once

#include "../Utilities/Singleton.h"

#include <iostream>
#include <list>
//#include <string>

#define _WATCHPOINT Debug::Watchpoint(__FILE__, __LINE__, __FUNCTION__);

namespace Symphony
{
    class Debug : public Singleton<Debug>
    {
        friend class Singleton<Debug>;
    public:
        
        static void Log(std::string);
        static void LogWarning(std::string);
        static void LogError(std::string);
        static void Watchpoint(const char* file, int line, const char* function);

    protected:
        std::list<std::string> log, warningLog, errorLog;

        void InternalLog(std::string);
        void InternalLogWarning(std::string);
        void InternalLogError(std::string);
        void InternalWatchpoint(const char* file, int line, const char* function);
    };
}