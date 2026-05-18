#pragma once
#include "WidgetsEvents/Callback.h"


namespace Blade {

struct TextFieldEvents
{
    CallbackString change;
    CallbackBool focus;
};

} // namespace