#include "NativeButtonEvents.h"


namespace Blade::Backend {

namespace {

auto ApplyClick(CommandRouter& router, Api::Id id) -> void
{
    router.on(
        id,
        BN_CLICKED,
        { .type = Api::Events::Click }
    );
}

auto ApplyFocus(CommandRouter& router, Api::Id id) -> void
{
    router.on(
        id,
        BN_SETFOCUS,
        { .type = Api::Events::Focus, .payload = true }
    );

    router.on(
        id,
        BN_KILLFOCUS,
        { .type = Api::Events::Focus, .payload = false }
    );
}

} // namespace

auto NativeButtonEvents::Apply(CommandRouter& router, Api::Id id, const Api::EventSubscriptions& events) -> void
{
    for (const auto event : events)
    {
        switch (event)
        {
        case Api::Events::Click:
            ApplyClick(router, id);
            break;

        case Api::Events::Focus:
            ApplyFocus(router, id);
            break;

        default:
            break;
        }
    }
}

} // namespace Blade::Backend
