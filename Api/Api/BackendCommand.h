#pragma once
#include "CommandType.h"
#include "Common/Property.h"
#include "Common/Types.h"


namespace Blade::Api {


struct BackendCommand
{
    Api::CommandType command;

    Api::Id id;

    Api::Id parent = 0;

    // TODO enum?
    Api::Text nodeType; // "Button", "Window", "Column"

    Api::PropertyMap props;
    Api::EventMap events;
};
} // namespace
