#include "NativeTrayApi.h"

#include "Common/Logger.h"

namespace Blade::Backend {

namespace {

constexpr UINT_PTR SubclassId = 1;

} // namespace

auto NativeTrayApi::Notify(DWORD message, NOTIFYICONDATAW& data, Api::Id id) -> bool
{
    if (Shell_NotifyIconW(message, &data)) return true;

    LOGF_E(L"[Error] NativeTray::Shell_NotifyIcon failed id=%d message=%lu [%lu]", id, message, GetLastError());
    return false;
}

auto NativeTrayApi::SetSubclass(HWND hwnd, SUBCLASSPROC proc, DWORD_PTR data) -> void
{
    SetWindowSubclass(hwnd, proc, SubclassId, data);
}

auto NativeTrayApi::RemoveSubclass(HWND hwnd, SUBCLASSPROC proc) -> void
{
    RemoveWindowSubclass(hwnd, proc, SubclassId);
}

auto NativeTrayApi::DestroyIcon(HICON icon) -> void
{
    if (icon) ::DestroyIcon(icon);
}

} // namespace Blade::Backend
