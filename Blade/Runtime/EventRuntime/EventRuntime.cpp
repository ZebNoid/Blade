#include "EventRuntime.h"


namespace Blade {

namespace {

template <typename... THandlers>
struct Overloaded : THandlers...
{
    using THandlers::operator()...;
};

} // namespace

auto EventRuntime::registerTree(
    const WidgetTree& tree
) -> void
{
    if (!tree.events.empty())
    {
        m_events.insert_or_assign(
            tree.id,
            tree.events
        );
    }

    for (const auto& child : tree.children)
    {
        registerTree(child);
    }
}

auto EventRuntime::dispatch(
    const Api::BackendEvent& event
) -> Api::EventResult
{
    const auto nodeIt = m_events.find(event.target);

    if (nodeIt == m_events.end())
    {
        return {};
    }

    const auto eventIt = nodeIt->second.find(event.type);

    if (eventIt == nodeIt->second.end())
    {
        return {};
    }

    return std::visit(
        Overloaded{
            [](const Api::CallbackVoid& callback) -> Api::EventResult
            {
                if (callback)
                {
                    callback();
                }

                return {};
            },

            [](const Api::CallbackResult& callback) -> Api::EventResult
            {
                return callback
                    ? callback()
                    : Api::EventResult{};
            },

            [&event](const Api::CallbackString& callback) -> Api::EventResult
            {
                if (callback)
                {
                    if (const auto* value = std::get_if<Api::Text>(&event.value))
                    {
                        callback(*value);
                    }
                }

                return {};
            },

            [&event](const Api::CallbackBool& callback) -> Api::EventResult
            {
                if (callback)
                {
                    if (const auto* value = std::get_if<bool>(&event.value))
                    {
                        callback(*value);
                    }
                }

                return {};
            }
        },
        eventIt->second
    );
}

} // namespace Blade
