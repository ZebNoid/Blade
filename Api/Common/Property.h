#pragma once
#include <functional>
#include <variant>

#include "LayoutProps.h"
#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "Types.h"


namespace Blade::Api {

using EventCallback = std::function<void()>;


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


using EventMap = std::unordered_map<Api::Text, EventCallback>;
using PropertyMap = std::unordered_map<Api::Text, PropertyValue>;


} // namespace
