#include "AppCommandDispatcher.h"

#include "App/AppBackend.h"
#include "Components/Tray/NativeTray.h"
#include "Node/NativeNode/NativeNode.h"
#include "WinApi/HwndApi/HwndApi.h"

namespace Blade::Backend {

namespace {

auto Native(AppBackend* backend, Api::Id target) -> INativeElement*
{
    if (!backend || target == Api::InvalidId) return nullptr;

    auto* node = backend->nodes().get(target);
    return node ? node->native.get() : nullptr;
}

auto Hwnd(AppBackend* backend, Api::Id target) -> HWND
{
    auto* native = Native(backend, target);
    return native ? native->handle() : nullptr;
}

auto Tray(AppBackend* backend, Api::Id target) -> NativeTray*
{
    return dynamic_cast<NativeTray*>(Native(backend, target));
}

auto TextPayload(const Api::AppCommand& command) -> const Api::Text*
{
    return std::get_if<Api::Text>(&command.payload);
}

template <typename Apply>
auto ApplyHwnd(AppBackend* backend, Api::Id target, Apply apply) -> void
{
    if (const auto hwnd = Hwnd(backend, target)) apply(hwnd);
}

} // namespace

AppCommandDispatcher::AppCommandDispatcher(AppBackend* backend) : m_backend(backend)
{
}

auto AppCommandDispatcher::dispatch(const Api::AppCommand& command) -> void
{
    switch (command.command)
    {
    case Api::AppCommandType::Quit:
        if (m_backend) m_backend->quit();
        break;

    case Api::AppCommandType::CloseWindow:
        ApplyHwnd(m_backend, command.target, [](HWND hwnd) { HwndApi::Close(hwnd); });
        break;

    case Api::AppCommandType::Show:
        ApplyHwnd(m_backend, command.target, [](HWND hwnd) { HwndApi::SetVisible(hwnd, true); });
        break;

    case Api::AppCommandType::Hide:
        ApplyHwnd(m_backend, command.target, [](HWND hwnd) { HwndApi::SetVisible(hwnd, false); });
        break;

    case Api::AppCommandType::MinimizeWindow:
        ApplyHwnd(m_backend, command.target, [](HWND hwnd) { HwndApi::Show(hwnd, SW_MINIMIZE); });
        break;

    case Api::AppCommandType::MaximizeWindow:
        ApplyHwnd(m_backend, command.target, [](HWND hwnd) { HwndApi::Show(hwnd, SW_MAXIMIZE); });
        break;

    case Api::AppCommandType::RestoreWindow:
        ApplyHwnd(m_backend, command.target, [](HWND hwnd) { HwndApi::Show(hwnd, SW_RESTORE); });
        break;

    case Api::AppCommandType::SetTrayIcon:
        if (auto* tray = Tray(m_backend, command.target); tray)
        {
            if (const auto* icon = TextPayload(command)) tray->setIcon(*icon);
        }
        break;

    case Api::AppCommandType::SetTrayTitle:
        if (auto* tray = Tray(m_backend, command.target); tray)
        {
            if (const auto* title = TextPayload(command)) tray->setTitle(*title);
        }
        break;

    default:
        break;
    }
}

} // namespace Blade::Backend
