#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {


class NativePropertyMapper
{
public:
    static auto Apply(
        HWND hwnd, // TODO NativeComponent
        const Api::PropertyMap& props
    ) -> void;
};


} // namespace
