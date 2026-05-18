#pragma once
#include <functional>


namespace Blade {

// using EventHandler = std::function<void(const EventValue&)>;
using CallbackVoid = std::function<void()>;
using CallbackString = std::function<void(std::string)>;
using CallbackBool = std::function<void(bool)>;

// TODO EventCallback
template<typename... Args>
using EventCallback = std::function<void(Args...)>;
// EventCallback<int, int>

} // namespace