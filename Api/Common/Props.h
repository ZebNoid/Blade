#pragma once

namespace Blade::Api {


enum class Props
{
    Unknown,
    IsDefault,
    Title,
    Size,
    Position,
    Rect,
    Visible,
    Caption,

    Layout,
    Gap
};

inline auto to_string(Props p) -> std::wstring {
    switch (p) {
    case Props::Unknown:   return L"Unknown";
    case Props::IsDefault:   return L"IsDefault";
    case Props::Title:   return L"Title";
    case Props::Size:   return L"Size";
    case Props::Position:   return L"Position";
    case Props::Rect:   return L"Rect";
    case Props::Visible:   return L"Visible";
    case Props::Caption:   return L"Caption";

    case Props::Layout:   return L"Layout";
    case Props::Gap:   return L"Gap";
    default:           return L"Unknown";
    }
}

} // namespace
