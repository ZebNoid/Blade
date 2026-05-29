#pragma once

namespace Blade::Api {

enum class AppCommandType
{
    Quit,
    CloseWindow,
    ShowWindow,
    HideWindow,
    MinimizeWindow,
    MaximizeWindow,
    RestoreWindow,
    SetTrayIcon,
    SetTrayTitle
};

inline auto to_string(AppCommandType c) -> std::wstring
{
    switch (c)
    {
    case AppCommandType::Quit: return L"Quit";
    case AppCommandType::CloseWindow: return L"CloseWindow";
    case AppCommandType::ShowWindow: return L"ShowWindow";
    case AppCommandType::HideWindow: return L"HideWindow";
    case AppCommandType::MinimizeWindow: return L"MinimizeWindow";
    case AppCommandType::MaximizeWindow: return L"MaximizeWindow";
    case AppCommandType::RestoreWindow: return L"RestoreWindow";
    case AppCommandType::SetTrayIcon: return L"SetTrayIcon";
    case AppCommandType::SetTrayTitle: return L"SetTrayTitle";
    default: return L"Unknown";
    }
}

} // namespace Blade::Api
