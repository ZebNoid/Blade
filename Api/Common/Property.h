#pragma once
#include <functional>
#include <variant>
#include <vector>

#include "Callbacks.h"
#include "CaptionProps.h"
#include "Events/Events.h"
#include "Lifetime.h"
#include "MenuTrigger.h"
#include "MenuData.h"
#include "Point.h"
#include "Props.h"
#include "Rect.h"
#include "Shortcut.h"
#include "Size.h"
#include "Types.h"
#include "WindowPlacementProps.h"
#include "WindowState.h"


namespace Blade::Api {

using EventsValue = std::variant<
    CallbackVoid,
    CallbackResult,
    CallbackString,
    CallbackBool
>;

using PropertyValue = std::variant<
    bool,
    int,
    float,
    double,
    Api::Id,
    Api::Text,
    Api::Point,
    Api::Size,
    Api::Rect,
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
