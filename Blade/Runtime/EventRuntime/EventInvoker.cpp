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

    const auto* value = std::get_if<Api::Text>(&event.payload);

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

    const auto* value = std::get_if<bool>(&event.payload);

    if (!value)
    {
        return {};
    }

    callback(*value);
    return {};
}

auto InvokeCallback(const Api::CallbackContext& callback, Api::EventContext& context) -> Api::EventResult
{
    if (!callback)
    {
        return {};
    }

    callback(context);
    return {};
}

auto InvokeCallback(const Api::CallbackContextResult& callback, Api::EventContext& context) -> Api::EventResult
{
    if (!callback)
    {
        return {};
    }

    return callback(context);
}

} // namespace

auto InvokeEvent(const Api::EventsValue& callback, const Api::BackendEvent& event, Api::EventContext& context) -> Api::EventResult
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

    if (const auto* value = std::get_if<Api::CallbackContext>(&callback))
    {
        return InvokeCallback(*value, context);
    }

    if (const auto* value = std::get_if<Api::CallbackContextResult>(&callback))
    {
        return InvokeCallback(*value, context);
    }

    return {};
}

} // namespace Blade
