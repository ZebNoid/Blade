#pragma once
#include <functional>
#include <variant>

#include "Callbacks.h"
#include "LayoutProps.h"
#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "Types.h"


namespace Blade::Api {

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

using EventMap = std::unordered_map<Api::Text, CallbackVoid>; // TODO variant


} // namespace
