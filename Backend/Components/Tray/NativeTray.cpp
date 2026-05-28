#include "NativeTray.h"

#include <commctrl.h>

#include "Common/Logger.h"
#include "Property/PropertyReader.h"
#include "WinApi/Resource/ImageLoader/ImageLoader.h"
#include "WinApi/Window/Hwnd/Hwnd.h"

namespace Blade::Backend {

namespace {

constexpr UINT TrayCallback = WM_APP + 1;
constexpr UINT_PTR SubclassId = 1;

auto CopyTip(NOTIFYICONDATAW& data, const Api::Text& title) -> void
{
    wcsncpy_s(data.szTip, title.c_str(), _TRUNCATE);
}

} // namespace

NativeTray::~NativeTray()
{
    if (m_hwnd)
    {
        Shell_NotifyIconW(NIM_DELETE, &m_data);
        RemoveWindowSubclass(m_hwnd, Proc, SubclassId);
        DestroyWindow(m_hwnd);
    }

    if (m_icon) DestroyIcon(m_icon);
}

auto NativeTray::create(HINSTANCE hInstance, Api::Id id, Api::BackendMessageHandler* handler) -> bool
{
    m_id = id;
    m_commandRouter.setHandler(handler);

    m_hwnd = Hwnd::Create({
        .className = L"STATIC",
        .windowName = L"BladeTray",
        .style = 0,
        .hInstance = hInstance,
    });

    if (!m_hwnd) return false;

    SetWindowSubclass(m_hwnd, Proc, SubclassId, reinterpret_cast<DWORD_PTR>(this));

    m_data.cbSize = sizeof(NOTIFYICONDATAW);
    m_data.hWnd = m_hwnd;
    m_data.uID = m_id;
    m_data.uFlags = NIF_MESSAGE | NIF_TIP;
    m_data.uCallbackMessage = TrayCallback;

    return notify(NIM_ADD);
}

auto CALLBACK NativeTray::Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR id, DWORD_PTR data) -> LRESULT
{
    auto* self = reinterpret_cast<NativeTray*>(data);

    if (!self) return DefSubclassProc(hwnd, msg, wParam, lParam);

    if (const auto result = self->handle(msg, wParam, lParam))
    {
        return *result;
    }

    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

auto NativeTray::handle(UINT msg, WPARAM, LPARAM lParam) -> std::optional<LRESULT>
{
    if (msg != TrayCallback || !m_contextMenu) return {};

    switch (lParam)
    {
    case WM_RBUTTONUP:
        m_contextMenu->showAtCursor(Api::MenuTrigger::RightClick);
        return 0;

    case WM_MBUTTONUP:
        m_contextMenu->showAtCursor(Api::MenuTrigger::MiddleClick);
        return 0;

    case WM_LBUTTONUP:
        m_contextMenu->showAtCursor(Api::MenuTrigger::LeftClick);
        return 0;

    default:
        return {};
    }
}

auto NativeTray::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* title = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Title))
    {
        updateTitle(*title);
    }

    if (const auto* icon = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Icon))
    {
        updateIcon(*icon);
    }

    if (const auto* menus = PropertyReader::Get<Api::ContextMenus>(propertyMap, Api::Props::ContextMenus))
    {
        updateContextMenus(*menus);
    }
}

auto NativeTray::applyEvents(const Api::EventSubscriptions&) -> void
{
}

auto NativeTray::isAlive() const -> bool
{
    return m_alive;
}

auto NativeTray::attachChild(INativeElement*) -> void
{
}

auto NativeTray::updateIcon(const Api::Text& path) -> void
{
    if (m_icon)
    {
        DestroyIcon(m_icon);
        m_icon = nullptr;
    }

    m_icon = ImageLoader::LoadIcon(path, 16, 16);

    if (m_icon)
    {
        m_data.hIcon = m_icon;
        m_data.uFlags |= NIF_ICON;
        notify(NIM_MODIFY);
    }
}

auto NativeTray::updateTitle(const Api::Text& title) -> void
{
    CopyTip(m_data, title);
    notify(NIM_MODIFY);
}

auto NativeTray::updateContextMenus(const Api::ContextMenus& menus) -> void
{
    if (m_contextMenu || menus.empty()) return;

    auto contextMenu = std::make_unique<NativeContextMenu>();
    if (contextMenu->attach(m_hwnd, m_id, m_commandRouter, menus)) m_contextMenu = std::move(contextMenu);
}

auto NativeTray::notify(DWORD message) -> bool
{
    if (Shell_NotifyIconW(message, &m_data)) return true;

    LOGF_E(L"[Error] NativeTray::Shell_NotifyIcon failed id=%d message=%lu [%lu]", m_id, message, GetLastError());
    return false;
}

} // namespace Blade::Backend
