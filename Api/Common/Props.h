#pragma once

namespace Blade::Api {


enum class Props
{
    Unknown,
    Layout,
    Default,
    Title,
    Size,
    Position
};

inline auto to_string(Props p) -> std::wstring {
    switch (p) {
    case Props::Unknown:   return L"Unknown";
    case Props::Layout:   return L"Layout";
    case Props::Default:   return L"Default";
    case Props::Title:   return L"Title";
    case Props::Size:   return L"Size";
    case Props::Position:   return L"Position";
    default:           return L"Unknown";
    }
}

} // namespace
