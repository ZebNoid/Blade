#pragma once

#include "Common/Property.h"
#include "WinApi/Router/CommandRouter/CommandRouter.h"


namespace Blade::Backend {

class NativeButtonEvents
{
public:
    static auto Apply(CommandRouter& router, Api::Id id, const Api::EventSubscriptions& events) -> void;
};

} // namespace Blade::Backend
