#pragma once
#include <functional>

#include "Events.h"
#include "Types.h"

namespace Blade::Api {

using CallbackVoid = std::function<void()>;
using CallbackResult = std::function<Api::EventResult()>;
using CallbackString = std::function<void(Api::Text)>;
using CallbackBool = std::function<void(bool)>;

// TODO EventCallback
template <typename... Args>
using EventCallback = std::function<void(Args...)>;


} // namespace
