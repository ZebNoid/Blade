#include "NativeWindowEvents.h"

#include <algorithm>

#include "Components/Window/NativeWindow.h"
#include "WinApi/HwndApi/HwndApi.h"


namespace Blade::Backend {

namespace {

auto HasEvent(const Api::EventSubscriptions& events, Api::Events event) -> bool
{
    return std::ranges::find(events, event) != events.end();
}

} // namespace

auto NativeWindowEvents::Apply(NativeWindow& window, const Api::EventSubscriptions& events) -> void
{
    const bool hasClose = HasEvent(events, Api::Events::Close);

    window.router().on(
        WM_CLOSE,
        [&window, hasClose](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            if (hasClose)
            {
                window.commandRouter().emit({
                    .target = window.id(),
                    .type = Api::Events::Close
                });
            }

            HwndApi::Destroy(hwnd);
            return 0;
        }
    );
}

} // namespace Blade::Backend
