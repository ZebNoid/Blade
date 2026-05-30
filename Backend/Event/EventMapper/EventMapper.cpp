#include "EventMapper.h"

#include <algorithm>

#include "Components/Native/Button/NativeButtonEvents.h"
#include "Components/Native/Button/NativeButton.h"
#include "Components/Window/NativeWindowEvents.h"
#include "Components/Window/NativeWindow.h"


namespace Blade::Backend {

namespace {

auto HasEvent(const Api::EventSubscriptions& events, Api::Events event) -> bool
{
    return std::ranges::find(events, event) != events.end();
}

} // namespace

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
            window.commandRouter().emit({
                .type = Api::BackendMessageType::Destroyed,
                .payload = Api::BackendDestroyed{ .target = window.id() }
            });
            return 0;
        }
    );

    NativeWindowEvents::Apply(window, events);
}

auto EventMapper::Apply(NativeButton& button, const Api::EventSubscriptions& events) -> void
{
    if (HasEvent(events, Api::Events::Drop)) button.enableDropTarget();

    auto* parent = dynamic_cast<NativeWindow*>(button.parent());

    if (!parent)
    {
        return;
    }

    NativeButtonEvents::Apply(parent->commandRouter(), button.id(), events);
}

} // namespace Blade::Backend
