#include "NativeContextMenu.h"

#include <commctrl.h>
#include <windowsx.h>

#include "Common/Logger.h"

namespace Blade::Backend {

namespace {

constexpr UINT_PTR SubclassId = 1;

auto MenuItemId(Api::Id id) -> UINT_PTR
{
    return static_cast<UINT_PTR>(id);
}

} // namespace

NativeContextMenu::~NativeContextMenu()
{
    if (m_hwnd) RemoveWindowSubclass(m_hwnd, Proc, SubclassId);
}

auto NativeContextMenu::attach(HWND hwnd, Api::Id ownerId, CommandRouter& router, Api::ContextMenus menus) -> bool
{
    if (!hwnd || menus.empty()) return false;

    m_hwnd = hwnd;
    m_ownerId = ownerId;
    m_router = &router;
    m_menus = std::move(menus);

    if (!SetWindowSubclass(hwnd, Proc, SubclassId, reinterpret_cast<DWORD_PTR>(this)))
    {
        LOGF_E(L"[Error] NativeContextMenu::SetWindowSubclass failed id=%d hwnd=%p [%lu]", m_ownerId, hwnd, GetLastError());
        m_hwnd = nullptr;
        return false;
    }

    LOGF_D(L"NativeContextMenu::Attach id=%d hwnd=%p", m_ownerId, hwnd);
    return true;
}

auto CALLBACK NativeContextMenu::Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR id, DWORD_PTR data) -> LRESULT
{
    auto* self = reinterpret_cast<NativeContextMenu*>(data);

    if (!self) return DefSubclassProc(hwnd, msg, wParam, lParam);

    if (const auto result = self->handle(hwnd, msg, wParam, lParam))
    {
        return *result;
    }

    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

auto NativeContextMenu::handle(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> std::optional<LRESULT>
{
    switch (msg)
    {
    case WM_CONTEXTMENU:
        return showAtCursor(Api::MenuTrigger::RightClick) ? 0 : std::optional<LRESULT>{};

    case WM_LBUTTONUP:
        return showAtClientPoint(Api::MenuTrigger::LeftClick, lParam) ? 0 : std::optional<LRESULT>{};

    case WM_MBUTTONUP:
        return showAtClientPoint(Api::MenuTrigger::MiddleClick, lParam) ? 0 : std::optional<LRESULT>{};

    default:
        return {};
    }
}

auto NativeContextMenu::show(Api::MenuTrigger trigger, POINT point) -> bool
{
    const auto* data = find(trigger);
    if (!data || data->items.empty()) return false;

    auto menu = CreatePopupMenu();
    if (!menu) return false;

    for (const auto& item : data->items)
    {
        AppendMenuW(menu, MF_STRING, MenuItemId(item.id), item.title.c_str());
    }

    const auto command = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON, point.x, point.y, m_hwnd, nullptr);
    DestroyMenu(menu);

    if (command == 0 || !m_router) return true;

    m_router->emit({
        .target = static_cast<Api::Id>(command),
        .type = Api::Events::Click
    });

    return true;
}

auto NativeContextMenu::showAtCursor(Api::MenuTrigger trigger) -> bool
{
    POINT point{};
    GetCursorPos(&point);
    return show(trigger, point);
}

auto NativeContextMenu::showAtClientPoint(Api::MenuTrigger trigger, LPARAM lParam) -> bool
{
    POINT point{
        GET_X_LPARAM(lParam),
        GET_Y_LPARAM(lParam)
    };

    ClientToScreen(m_hwnd, &point);
    return show(trigger, point);
}

auto NativeContextMenu::find(Api::MenuTrigger trigger) const -> const Api::MenuData*
{
    for (const auto& menu : m_menus)
    {
        if (Api::Has(menu.trigger, trigger)) return &menu;
    }

    return nullptr;
}

} // namespace Blade::Backend
