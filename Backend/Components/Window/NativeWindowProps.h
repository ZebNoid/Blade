#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {

class NativeWindow;

class NativeWindowProps
{
public:
    static auto Apply(NativeWindow& window, const Api::PropertyMap& propertyMap) -> Api::PropertyMap;
};

} // namespace Blade::Backend
