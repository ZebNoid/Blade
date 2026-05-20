#pragma once
#include <functional>
#include <variant>

#include "Common/Common.h"



namespace Blade::Api {

using EventCallback = std::function<void()>;

using EventMap = std::unordered_map<Api::Text, EventCallback>;


using PropertyValue = std::variant<
    bool,
    int,
    float,
    double,
    Api::Text,
    Api::Point,
    Api::Size,
    Api::Rect,
    LayoutProps
>;

using PropertyMap = std::unordered_map<Api::Text, PropertyValue>;


} // namespace
