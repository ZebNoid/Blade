#pragma once

#include "Command/ElementCommandType.h"
#include "Common/Property.h"
#include "Common/Types.h"
#include "Widget/WidgetType.h"


namespace Blade::Api {

struct ElementCommand
{
    Api::ElementCommandType command;

    Api::Id id = InvalidId;
    Api::Id parent = InvalidId;

    Api::WidgetType nodeType = Api::WidgetTypes::Unknown;

    Api::PropertyMap props;
    Api::EventSubscriptions events;
};

} // namespace Blade::Api
