#pragma once
#include <functional>
#include <variant>
#include <vector>

#include "Callbacks.h"
#include "Events.h"
#include "LayoutProps.h"
#include "Point.h"
#include "Props.h"
#include "Rect.h"
#include "Size.h"
#include "Types.h"


namespace Blade::Api {

using EventsValue = std::variant<
    CallbackVoid,
    CallbackString,
    CallbackBool
>;

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


using PropertyMap = std::unordered_map<Api::Props, PropertyValue>;

using EventId = Api::Id;
using EventMap = std::unordered_map<Api::Events, EventsValue>;
using EventSubscriptions = std::vector<Api::Events>;


} // namespace
