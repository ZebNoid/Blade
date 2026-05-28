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

auto IsCanceled(const Api::EventResult& result) -> bool
{
    const auto* value = std::get_if<bool>(&result);
    return value && !*value;
}

} // namespace

auto NativeWindowEvents::Apply(NativeWindow& window, const Api::EventSubscriptions& events) -> void
{
    const bool hasClose = HasEvent(events, Api::Events::Close);
    const bool hasDrop = HasEvent(events, Api::Events::Drop);

    if (hasDrop) window.enableDropTarget();

    window.router().on(
        WM_CLOSE,
        [&window, hasClose](HWND hwnd, UINT, WPARAM, LPARAM) -> int
        {
            if (hasClose)
            {
                const auto result = window.commandRouter().emit({
                    .target = window.id(),
                    .type = Api::Events::Close
                });

                if (IsCanceled(result))
                {
                    return 0;
                }
            }

            HwndApi::Destroy(hwnd);
            return 0;
        }
    );
}

} // namespace Blade::Backend
