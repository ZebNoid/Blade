#pragma once

#include "Command/ElementCommandType.h"
#include "Common/Property.h"
#include "Common/Types.h"


namespace Blade::Api {

struct ElementCommand
{
    Api::ElementCommandType command;

    Api::Id id = InvalidId;
    Api::Id parent = InvalidId;

    // TODO enum?
    Api::Text nodeType; // "Button", "Window", "Column"

    Api::PropertyMap props;
    Api::EventSubscriptions events;
};

} // namespace Blade::Api
