#pragma once

#include <cwchar>
#include <iostream>
#include <windows.h>


namespace Blade::Log {

enum class Color
{
    Debug = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Info = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    Warning = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    Error = FOREGROUND_RED | FOREGROUND_INTENSITY
};

inline auto Print(
    Color color,
    const wchar_t* message
) -> void
{
    const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(handle, &info);

    SetConsoleTextAttribute(
        handle,
        static_cast<WORD>(color)
    );

    std::wcout << message << L'\n';

    SetConsoleTextAttribute(
        handle,
        info.wAttributes
    );
}

template <typename... TArgs>
inline auto PrintFormat(
    Color color,
    const wchar_t* format,
    TArgs... args
) -> void
{
    const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(handle, &info);

    SetConsoleTextAttribute(
        handle,
        static_cast<WORD>(color)
    );

    std::wprintf(
        format,
        args...
    );

    std::wprintf(L"\n");

    SetConsoleTextAttribute(
        handle,
        info.wAttributes
    );
}

} // namespace Blade::Log

#define LOG(message) ::Blade::Log::Print(::Blade::Log::Color::Info, message)
#define LOG_D(message) ::Blade::Log::Print(::Blade::Log::Color::Debug, message)
#define LOG_W(message) ::Blade::Log::Print(::Blade::Log::Color::Warning, message)
#define LOG_E(message) ::Blade::Log::Print(::Blade::Log::Color::Error, message)

#define LOGF(format, ...) ::Blade::Log::PrintFormat(::Blade::Log::Color::Info, format, __VA_ARGS__)
#define LOGF_D(format, ...) ::Blade::Log::PrintFormat(::Blade::Log::Color::Debug, format, __VA_ARGS__)
#define LOGF_W(format, ...) ::Blade::Log::PrintFormat(::Blade::Log::Color::Warning, format, __VA_ARGS__)
#define LOGF_E(format, ...) ::Blade::Log::PrintFormat(::Blade::Log::Color::Error, format, __VA_ARGS__)
