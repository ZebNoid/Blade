#pragma once

namespace Blade::Api {

enum class AppCommandType
{
    Quit,
    Show,
    Hide,
    WindowClose,
    WindowMinimize,
    WindowMaximize,
    WindowRestore,
    TrayIcon,
    TrayTitle,
    UnmountRoot
};

inline auto to_string(AppCommandType c) -> std::wstring
{
    switch (c)
    {
    case AppCommandType::Quit: return L"Quit";
    case AppCommandType::Show: return L"Show";
    case AppCommandType::Hide: return L"Hide";
    case AppCommandType::WindowClose: return L"WindowClose";
    case AppCommandType::WindowMinimize: return L"WindowMinimize";
    case AppCommandType::WindowMaximize: return L"WindowMaximize";
    case AppCommandType::WindowRestore: return L"WindowRestore";
    case AppCommandType::TrayIcon: return L"TrayIcon";
    case AppCommandType::TrayTitle: return L"TrayTitle";
    case AppCommandType::UnmountRoot: return L"UnmountRoot";
    default: return L"Unknown";
    }
}

} // namespace Blade::Api
