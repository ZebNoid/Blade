#pragma once

#include "Api/ApiBackend.h"


namespace Blade::Backend {

class NativeButton;
class NativeWindow;

class EventMapper
{
public:
    static auto Apply(NativeWindow& window, const Api::EventSubscriptions& events) -> void;
    static auto Apply(NativeButton& button, const Api::EventSubscriptions& events) -> void;
};

} // namespace Blade::Backend
