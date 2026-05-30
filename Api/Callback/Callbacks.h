#pragma once

#include <functional>
#include <type_traits>
#include <variant>

#include "Common/Types.h"
#include "Events/EventContext.h"
#include "Events/EventResult.h"

namespace Blade::Api {

using CallbackVoid = std::function<void()>;
using CallbackResult = std::function<Api::EventResult()>;
using CallbackString = std::function<void(Api::Text)>;
using CallbackBool = std::function<void(bool)>;
using CallbackContext = std::function<void(Api::EventContext&)>;
using CallbackContextResult = std::function<Api::EventResult(Api::EventContext&)>;

using EventsValue = std::variant<
    CallbackVoid,
    CallbackResult,
    CallbackString,
    CallbackBool,
    CallbackContext,
    CallbackContextResult
>;

class EventCallback
{
public:
    EventCallback() = default;
    EventCallback(std::nullptr_t) {}

    template <typename Callback>
        requires (!std::same_as<std::decay_t<Callback>, EventCallback>)
    EventCallback(Callback&& callback)
    {
        assign(std::forward<Callback>(callback));
    }

    auto value() const -> const EventsValue& { return m_value; }
    explicit operator bool() const;

private:
    template <typename Callback>
    auto assign(Callback&& callback) -> void
    {
        using T = std::decay_t<Callback>;

        if constexpr (std::is_invocable_r_v<Api::EventResult, T>)
        {
            m_value = CallbackResult(std::forward<Callback>(callback));
        }
        else if constexpr (std::is_invocable_r_v<void, T>)
        {
            m_value = CallbackVoid(std::forward<Callback>(callback));
        }
        else if constexpr (std::is_invocable_r_v<Api::EventResult, T, Api::EventContext&>)
        {
            m_value = CallbackContextResult(std::forward<Callback>(callback));
        }
        else if constexpr (std::is_invocable_r_v<void, T, Api::EventContext&>)
        {
            m_value = CallbackContext(std::forward<Callback>(callback));
        }
        else if constexpr (std::is_invocable_r_v<void, T, Api::Text>)
        {
            m_value = CallbackString(std::forward<Callback>(callback));
        }
        else if constexpr (std::is_invocable_r_v<void, T, bool>)
        {
            m_value = CallbackBool(std::forward<Callback>(callback));
        }
    }

private:
    EventsValue m_value;
};

inline EventCallback::operator bool() const
{
    return std::visit(
        [](const auto& callback)
        {
            return static_cast<bool>(callback);
        },
        m_value
    );
}

} // namespace Blade::Api
