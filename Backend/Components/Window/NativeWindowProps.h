#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {

class NativeWindowProps
{
public:
    static auto Apply(HWND hwnd, const Api::PropertyMap& propertyMap) -> Api::PropertyMap;
};

} // namespace Blade::Backend
