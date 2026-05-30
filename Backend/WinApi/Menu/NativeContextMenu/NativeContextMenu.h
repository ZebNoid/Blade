#pragma once

#include <optional>
#include <windows.h>

#include "Menu/MenuData.h"
#include "WinApi/Router/CommandRouter/CommandRouter.h"

namespace Blade::Backend {

class NativeContextMenu
{
public:
    NativeContextMenu() = default;
    ~NativeContextMenu();

    static auto Show(HWND hwnd, CommandRouter& router, const Api::ContextMenus& menus, Api::MenuTrigger trigger, POINT point) -> bool;

    auto attach(HWND hwnd, Api::Id ownerId, CommandRouter& router, Api::ContextMenus menus) -> bool;
    auto showAtCursor(Api::MenuTrigger trigger) -> bool;

private:
    static auto CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR id, DWORD_PTR data) -> LRESULT;

    auto handle(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> std::optional<LRESULT>;
    auto show(Api::MenuTrigger trigger, POINT point) -> bool;
    auto showAtClientPoint(Api::MenuTrigger trigger, LPARAM lParam) -> bool;
    auto find(Api::MenuTrigger trigger) const -> const Api::MenuData*;

private:
    HWND m_hwnd = nullptr;
    Api::Id m_ownerId = Api::InvalidId;
    CommandRouter* m_router = nullptr;
    Api::ContextMenus m_menus;
};

} // namespace Blade::Backend
