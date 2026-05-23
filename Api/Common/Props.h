#pragma once

namespace Blade::Api {


enum class Props
{
    Unknown,
    Default,
    Title,
    Size,
    Position,
    Rect,

    Layout,
    Gap
};

inline auto to_string(Props p) -> std::wstring {
    switch (p) {
    case Props::Unknown:   return L"Unknown";
    case Props::Default:   return L"Default";
    case Props::Title:   return L"Title";
    case Props::Size:   return L"Size";
    case Props::Position:   return L"Position";
    case Props::Rect:   return L"Rect";

    case Props::Layout:   return L"Layout";
    case Props::Gap:   return L"Gap";
    default:           return L"Unknown";
    }
}

} // namespace
