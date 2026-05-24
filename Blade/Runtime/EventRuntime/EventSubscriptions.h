#pragma once

#include "Api/ApiBackend.h"


namespace Blade {

auto ToEventSubscriptions(const Api::EventMap& events) -> Api::EventSubscriptions;

} // namespace Blade
