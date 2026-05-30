#pragma once

namespace Blade::Api {


enum class Props
{
    Unknown,
    IsDefault,
    Title,
    Source,
    Icon,
    Size,
    Position,
    Rect,
    Visible,
    Caption,
    Placement,
    Resizable,
    TopMost,
    Taskbar,
    MinSize,
    MaxSize,
    State,
    Lifetime,
    DropTarget,
    MenuTrigger,
    Shortcut,
    ContextMenus
};

inline auto to_string(Props p) -> std::wstring {
    switch (p) {
    case Props::Unknown:   return L"Unknown";
    case Props::IsDefault:   return L"IsDefault";
    case Props::Title:   return L"Title";
    case Props::Source:   return L"Source";
    case Props::Icon:   return L"Icon";
    case Props::Size:   return L"Size";
    case Props::Position:   return L"Position";
    case Props::Rect:   return L"Rect";
    case Props::Visible:   return L"Visible";
    case Props::Caption:   return L"Caption";
    case Props::Placement:   return L"Placement";
    case Props::Resizable:   return L"Resizable";
    case Props::TopMost:   return L"TopMost";
    case Props::Taskbar:   return L"Taskbar";
    case Props::MinSize:   return L"MinSize";
    case Props::MaxSize:   return L"MaxSize";
    case Props::State:   return L"State";
    case Props::Lifetime:   return L"Lifetime";
    case Props::DropTarget:   return L"DropTarget";
    case Props::MenuTrigger:   return L"MenuTrigger";
    case Props::Shortcut:   return L"Shortcut";
    case Props::ContextMenus:   return L"ContextMenus";
    default:           return L"Unknown";
    }
}

} // namespace
