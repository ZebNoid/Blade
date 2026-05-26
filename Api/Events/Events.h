#pragma once


namespace Blade::Api {

enum class Events
{
    Unknown,
    Click,
    Focus,
    Close,
    Resize
};

inline auto to_string(Events e) -> std::wstring
{
    switch (e)
    {
    case Events::Unknown: return L"Unknown";
    case Events::Click: return L"Click";
    case Events::Focus: return L"Focus";
    case Events::Close: return L"Close";
    case Events::Resize: return L"Resize";
    default: return L"Unknown";
    }
}

} // namespace Blade::Api
