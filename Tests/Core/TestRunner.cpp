#include "TestRunner.h"

#include <Windows.h>

#include <exception>
#include <iostream>

namespace Blade::Tests {

namespace {

auto PrintStatus(WORD color, const char* status, std::string_view name) -> void
{
    const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info{};

    const bool hasConsole = console != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(console, &info);
    if (hasConsole) SetConsoleTextAttribute(console, color);

    std::cout << status;

    if (hasConsole) SetConsoleTextAttribute(console, info.wAttributes);

    std::cout << " \"" << name << "\"\n";
}

} // namespace

auto TestRunner::Run(std::string_view name, const std::function<void()>& test) -> void
{
    try
    {
        test();
        ++m_passed;
        PrintStatus(FOREGROUND_GREEN | FOREGROUND_INTENSITY, "[OK]", name);
    }
    catch (const std::exception& error)
    {
        ++m_failed;
        PrintStatus(FOREGROUND_RED | FOREGROUND_INTENSITY, "[FAIL]", name);
        std::cout << "   " << error.what() << '\n';
    }
}

auto TestRunner::Result() const -> int
{
    const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info{};
    const bool hasConsole = console != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(console, &info);

    std::cout << "\nTests: ";

    if (hasConsole) SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << m_passed << " passed";

    if (hasConsole) SetConsoleTextAttribute(console, info.wAttributes);
    std::cout << ", ";

    if (hasConsole) SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << m_failed << " failed";

    if (hasConsole) SetConsoleTextAttribute(console, info.wAttributes);
    std::cout << '\n';

    return m_failed == 0 ? 0 : 1;
}

} // namespace Blade::Tests
