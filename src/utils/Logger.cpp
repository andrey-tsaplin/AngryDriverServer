#include "Logger.h"

using namespace std;

namespace Logger
{
    LogLevel currentLogLevel_ = LogLevel::ERROR;

    string LogLevelName(const LogLevel logLevel)
    {
        switch (logLevel)
        {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::VERBOSE:
                return "VERBOSE";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::NONE:
                return "NONE";
        }
        return "UNKNOWN_LOG_LEVEL";
    }

    void LogInternal(LogLevel level, const char *format, bool printLogLevel, va_list args)
    {
        if (level < currentLogLevel_)
        {
            return;
        }

        string formatStr;

        if (printLogLevel)
        {
            time_t now;
            time(&now);
            char isoTime[50];
            strftime(isoTime, sizeof isoTime, "[%F %T]", localtime(&now));

            formatStr = string(isoTime) + " " + LogLevelName(level) + ": ";
        }

        formatStr = formatStr + format + "\n";

        if (level >= LogLevel::WARNING)
        {
            vfprintf(stderr, formatStr.c_str(), args);
        } else
        {
            vfprintf(stdout, formatStr.c_str(), args);
        }
    };

    void Log(LogLevel level, const char *format, bool printLogLevel, ...)
    {
        va_list args;
        va_start(args, printLogLevel);
        va_end(args);
        LogInternal(level, format, printLogLevel, args);
    };

    void Debug(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        va_end(args);
        LogInternal(LogLevel::DEBUG, format, true, args);
    }

    void Verbose(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        va_end(args);
        LogInternal(LogLevel::VERBOSE, format, true, args);
    }


    void Warning(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        va_end(args);
        LogInternal(LogLevel::WARNING, format, true, args);
    }


    void Error(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        va_end(args);
        LogInternal(LogLevel::ERROR, format, true, args);
    }


    void SetLogLevel(LogLevel newLogLevel)
    {
        currentLogLevel_ = newLogLevel;
        Verbose("Log level is %s", LogLevelName(currentLogLevel_).c_str());
    };
}
