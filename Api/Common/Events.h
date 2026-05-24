#pragma once

namespace Blade::Api {


enum class Events
{
    Unknown,
    Click,
    Close
};


inline auto to_string(Events e) -> std::wstring
{
    switch (e)
    {
    case Events::Unknown: return L"Unknown";
    case Events::Click: return L"Click";
    case Events::Close: return L"Close";
    default: return L"Unknown";
    }
}

} // namespace
