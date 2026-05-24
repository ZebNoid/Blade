#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {

class NativeButtonProps
{
public:
    static auto Apply(HWND hwnd, const Api::PropertyMap& propertyMap) -> void;
};

} // namespace Blade::Backend
