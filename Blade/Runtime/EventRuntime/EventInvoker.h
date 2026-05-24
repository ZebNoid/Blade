#pragma once

#include "Api/ApiBackend.h"


namespace Blade {

auto InvokeEvent(const Api::EventsValue& callback, const Api::BackendEvent& event) -> Api::EventResult;

} // namespace Blade
