#pragma once
#include <functional>
#include <variant>
#include <vector>

#include "Callbacks.h"
#include "Window/CaptionProps.h"
#include "Color.h"
#include "Events/Events.h"
#include "Lifetime.h"
#include "Menu/MenuTrigger.h"
#include "Menu/MenuData.h"
#include "Geometry/Point.h"
#include "Props.h"
#include "Geometry/Rect.h"
#include "Menu/Shortcut.h"
#include "Geometry/Size.h"
#include "Types.h"
#include "Window/WindowPlacementProps.h"
#include "Window/WindowState.h"


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
    Api::Color,
    Api::CaptionProps,
    Api::Lifetime,
    Api::MenuTrigger,
    Api::Shortcut,
    Api::ContextMenus,
    Api::WindowPlacementProps,
    Api::WindowState
>;


using PropertyMap = std::unordered_map<Api::Props, PropertyValue>;

using EventId = Api::Id;
using EventMap = std::unordered_map<Api::Events, EventsValue>;
using EventSubscriptions = std::vector<Api::Events>;


} // namespace
