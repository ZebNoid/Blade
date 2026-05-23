#pragma once

#include <iostream>


namespace Blade::Api {

enum class LogLevel
{
    Debug,
    Info,
    Error,
    Off
};

class Logger
{
public:
    static auto SetLevel(
        LogLevel level
    ) -> void
    {
        CurrentLevel() = level;
    }

    template <typename... TParts>
    static auto Debug(
        const TParts&... parts
    ) -> void
    {
        Write(
            LogLevel::Debug,
            std::wcout,
            parts...
        );
    }

    template <typename... TParts>
    static auto Info(
        const TParts&... parts
    ) -> void
    {
        Write(
            LogLevel::Info,
            std::wcout,
            parts...
        );
    }

    template <typename... TParts>
    static auto Error(
        const TParts&... parts
    ) -> void
    {
        Write(
            LogLevel::Error,
            std::wcerr,
            parts...
        );
    }

private:
    static auto CurrentLevel() -> LogLevel&
    {
        static LogLevel level = LogLevel::Debug;
        return level;
    }

    static auto CanWrite(
        LogLevel level
    ) -> bool
    {
        return level >= CurrentLevel() &&
            CurrentLevel() != LogLevel::Off;
    }

    template <typename TStream, typename... TParts>
    static auto Write(
        LogLevel level,
        TStream& stream,
        const TParts&... parts
    ) -> void
    {
        if (!CanWrite(level))
        {
            return;
        }

        (stream << ... << parts);
        stream << L'\n';
    }
};

} // namespace Blade::Api
