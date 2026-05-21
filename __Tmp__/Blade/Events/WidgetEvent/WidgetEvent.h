#pragma once

#include <functional>
#include <string>
#include <variant>


namespace Blade {


using EventValue = std::variant<
    std::monostate,
    bool,
    int,
    float,
    std::string
>;

using EventHandler = std::function<void(const EventValue&)>;


enum class WidgetEvent
{
    Click,
    Change,
    Focus,
};


} // namespace
