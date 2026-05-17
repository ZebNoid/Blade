#pragma once
#include "WidgetsCallbacks/Callback.h"


namespace Blade {

struct TextFieldCallbacks
{
    CallbackString change;
    CallbackBool focus;
};

} // namespace