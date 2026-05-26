#include "EventMapper.h"

#include "Components/Button/NativeButtonEvents.h"
#include "Components/Button/NativeButton.h"
#include "Components/Window/NativeWindowEvents.h"
#include "Components/Window/NativeWindow.h"


namespace Blade::Backend {

auto EventMapper::Apply(NativeWindow& window, const Api::EventSubscriptions& events) -> void
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

    NativeWindowEvents::Apply(window, events);
}

// TODO not NativeButton but all NativeElements
auto EventMapper::Apply(NativeButton& button, const Api::EventSubscriptions& events) -> void
{
    auto* parent = dynamic_cast<NativeWindow*>(button.parent());

    if (!parent)
    {
        return;
    }

    NativeButtonEvents::Apply(parent->commandRouter(), button.id(), events);
}

} // namespace Blade::Backend
