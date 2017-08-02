#include "Debugging.h"

#if _DEBUG

#   include <string>
#   include <cstdarg>

//TO-DO: Should _WIN32 be wrapped somewhere?
#   if _WIN32
#       include <windows.h>   // WinApi header
#       define SET_TERMINAL_TEXT_COLOR(color) \
            {\
                if (HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE)) \
                {\
                    SetConsoleTextAttribute(hConsole, color);\
                }\
            }
#   else
#       define SET_TERMINAL_TEXT_COLOR(color)
#   endif

namespace Symphony
{
    SINGLETON_INSTANCE_INIT(Debug)

    Debug::Debug()  {}
    Debug::~Debug() {}

    void Debug::DoLogF(const char* format, ...)
    {
        va_list arg;
        char buffer[MESSAGE_BUFFER_SIZE];
        va_start(arg, format);
        int ret = vsprintf_s(buffer, format, arg);
        va_end(arg);

        Instance()->InternalLog(buffer);
    }

    void Debug::DoLogInfoF(const char* format, ...)
    {
        va_list arg;
        char buffer[MESSAGE_BUFFER_SIZE];
        va_start(arg, format);
        int ret = vsprintf_s(buffer, format, arg);
        va_end(arg);

        Instance()->InternalLogInfo(buffer);
    }

    void Debug::DoLogWarningF(const char* format, ...)
    {
        va_list arg;
        char buffer[MESSAGE_BUFFER_SIZE];
        va_start(arg, format);
        int ret = vsprintf_s(buffer, format, arg);
        va_end(arg);

        Instance()->InternalLogWarning(buffer);
    }

    void Debug::DoLogErrorF(const char* format, ...)
    {
        va_list arg;
        char buffer[MESSAGE_BUFFER_SIZE];
        va_start(arg, format);
        int ret = vsprintf_s(buffer, format, arg);
        va_end(arg);

        Instance()->InternalLogError(buffer);
    }

    
    void Debug::InternalLog(const char* message)
    {
        //SET_TERMINAL_TEXT_COLOR(7);
        //log.push_back(message);
        std::cout << message << std::endl;
    }

    void Debug::InternalLogInfo(const char* message)
    {
        SET_TERMINAL_TEXT_COLOR(INFO_COLOR);
        //warningLog.push_back(message);
        std::cout << message << std::endl;
        SET_TERMINAL_TEXT_COLOR(LOG_COLOR);
    }

    void Debug::InternalLogWarning(const char* message)
    {
        SET_TERMINAL_TEXT_COLOR(WARNING_COLOR);
        //warningLog.push_back(message);
        std::cout << message << std::endl;
        SET_TERMINAL_TEXT_COLOR(LOG_COLOR);
    }

    void Debug::InternalLogError(const char* message)
    {
        SET_TERMINAL_TEXT_COLOR(ERROR_COLOR);
        //errorLog.push_back(message);
        std::cout << message << std::endl;
        SET_TERMINAL_TEXT_COLOR(LOG_COLOR);
    }

    bool Debug::DoAssertTest(bool condition, const char* msgTitle, const char* msgBody)
    {
        if (!condition)
        {
            int msgboxID = MessageBox(
                NULL,
                msgBody,
                msgTitle,
                MB_ICONERROR | MB_ABORTRETRYIGNORE | MB_DEFBUTTON2
            );
            
            Debug::DoLogError(msgBody);

            switch (msgboxID)
            {
            case IDABORT:
                //TODO1: Flush debug log into disk
                //TODO2: Should the resources be freed when doing a force exit?
                exit(-1);
                break;
            case IDRETRY:
                break;
            case IDIGNORE:
                break;
            }
        }

        return condition;
    }

    bool Debug::DoAssertTestWithFormat(bool condition, const char* msgTitle, const char* msgBodyFormat, ...)
    {
        va_list arg;
        char buffer[MESSAGE_BUFFER_SIZE];
        va_start(arg, msgBodyFormat);
        int ret = vsprintf_s(buffer, msgBodyFormat, arg);
        va_end(arg);

        return DoAssertTest(condition, msgTitle, buffer);
    }
}

#endif