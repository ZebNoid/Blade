#pragma once

namespace Blade::Api {

enum class AppCommandType
{
    Quit,
    Show,
    Hide,
    CloseWindow,
    MinimizeWindow,
    MaximizeWindow,
    RestoreWindow,
    SetTrayIcon,
    SetTrayTitle,
    DestroyRoot
};

inline auto to_string(AppCommandType c) -> std::wstring
{
    switch (c)
    {
    case AppCommandType::Quit: return L"Quit";
    case AppCommandType::Show: return L"Show";
    case AppCommandType::Hide: return L"Hide";
    case AppCommandType::CloseWindow: return L"CloseWindow";
    case AppCommandType::MinimizeWindow: return L"MinimizeWindow";
    case AppCommandType::MaximizeWindow: return L"MaximizeWindow";
    case AppCommandType::RestoreWindow: return L"RestoreWindow";
    case AppCommandType::SetTrayIcon: return L"SetTrayIcon";
    case AppCommandType::SetTrayTitle: return L"SetTrayTitle";
    case AppCommandType::DestroyRoot: return L"DestroyRoot";
    default: return L"Unknown";
    }
}

} // namespace Blade::Api
