#include "EventMapper.h"

#include "Components/Button/NativeButton.h"
#include "WinApi/NativeApi/NativeApi.h"
#include "Components/Window/NativeWindow.h"


namespace Blade::Backend {

auto EventMapper::Apply(NativeWindow& window, const Api::EventSubscriptions&) -> void
{
    window.router().on(
        WM_COMMAND,
        [&window](HWND, UINT, WPARAM wParam, LPARAM lParam) -> int
        {
            return window.commandRouter().dispatch(wParam, lParam) ? 0 : 1;
        }
    );

    window.router().on(
        WM_DESTROY,
        [&window](HWND, UINT, WPARAM, LPARAM) -> int
        {
            window.markDead();
            return 0;
        }
    );

    window.router().on(
        WM_CLOSE,
        [](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            NativeApi::Destroy(hwnd);
            return 0;
        }
    );
}

// TODO not NativeButton but all NativeElements
auto EventMapper::Apply(NativeButton& button, const Api::EventSubscriptions& events) -> void
{
    auto* parent = dynamic_cast<NativeWindow*>(button.parent());

    if (!parent)
    {
        return;
    }

    for (const auto event : events)
    {
        if (event == Api::Events::Click || event == Api::Events::Focus)
        {
            parent->commandRouter().on(button.id(), event);
        }
    }
}

} // namespace Blade::Backend
