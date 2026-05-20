#pragma once

#include <unordered_map>
#include <variant>

#include "Common/Common.h"

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


} // namespace