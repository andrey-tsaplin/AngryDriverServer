#include <stdio.h>
#include <string>
#include <cstring>
#include <stdarg.h>

#pragma once

using namespace std;

namespace Logger
{

    enum LogLevel
    {
        DEBUG,
        VERBOSE,
        WARNING,
        ERROR,
        NONE
    };

    extern LogLevel currentLogLevel_;

    string LogLevelName(const LogLevel logLevel);

    void LogInternal(LogLevel level, const char *format, bool printLogLevel, va_list args);

    void Log(LogLevel level, const char *format, bool printLogLevel = true, ...);

    void Debug(const char *format, ...);

    void Verbose(const char *format, ...);

    void Warning(const char *format, ...);

    void Error(const char *format, ...);

    void SetLogLevel(LogLevel newLogLevel);
}
