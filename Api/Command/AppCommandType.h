#pragma once

namespace Blade::Api {

enum class AppCommandType
{
    Quit
};

inline auto to_string(AppCommandType c) -> std::wstring
{
    switch (c)
    {
    case AppCommandType::Quit: return L"Quit";
    default: return L"Unknown";
    }
}

} // namespace Blade::Api
