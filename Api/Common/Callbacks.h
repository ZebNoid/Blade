#pragma once
#include <functional>


namespace Blade::Api {

using CallbackVoid = std::function<void()>;
using CallbackString = std::function<void(Api::Text)>;
using CallbackBool = std::function<void(bool)>;

// TODO EventCallback
template <typename... Args>
using EventCallback = std::function<void(Args...)>;


} // namespace
