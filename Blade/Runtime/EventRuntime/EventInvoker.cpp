#include "EventInvoker.h"


namespace Blade {

namespace {

auto InvokeCallback(const Api::CallbackVoid& callback) -> Api::EventResult
{
    if (callback)
    {
        callback();
    }

    return {};
}

auto InvokeCallback(const Api::CallbackResult& callback) -> Api::EventResult
{
    if (!callback)
    {
        return {};
    }

    return callback();
}

auto InvokeCallback(const Api::CallbackString& callback, const Api::BackendEvent& event) -> Api::EventResult
{
    if (!callback)
    {
        return {};
    }

    const auto* value = std::get_if<Api::Text>(&event.value);

    if (!value)
    {
        return {};
    }

    callback(*value);
    return {};
}

auto InvokeCallback(const Api::CallbackBool& callback, const Api::BackendEvent& event) -> Api::EventResult
{
    if (!callback)
    {
        return {};
    }

    const auto* value = std::get_if<bool>(&event.value);

    if (!value)
    {
        return {};
    }

    callback(*value);
    return {};
}

} // namespace

auto InvokeEvent(const Api::EventsValue& callback, const Api::BackendEvent& event) -> Api::EventResult
{
    if (const auto* value = std::get_if<Api::CallbackVoid>(&callback))
    {
        return InvokeCallback(*value);
    }

    if (const auto* value = std::get_if<Api::CallbackResult>(&callback))
    {
        return InvokeCallback(*value);
    }

    if (const auto* value = std::get_if<Api::CallbackString>(&callback))
    {
        return InvokeCallback(*value, event);
    }

    if (const auto* value = std::get_if<Api::CallbackBool>(&callback))
    {
        return InvokeCallback(*value, event);
    }

    return {};
}

} // namespace Blade
