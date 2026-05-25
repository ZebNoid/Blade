#pragma once

#include "Common/Property.h"


namespace Blade::Backend {

class NativeWindow;

class NativeWindowEvents
{
public:
    static auto Apply(NativeWindow& window, const Api::EventSubscriptions& events) -> void;
};

} // namespace Blade::Backend
