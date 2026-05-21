#pragma once

#include <windows.h>

#include "Common/Size.h"
#include "Common/Types.h"


namespace Blade::Backend {


class NativeApi
{
public:
    static auto setTitle(
        HWND hwnd,
        const Api::Text& text
    ) -> void;

    static auto setSize(
        HWND hwnd,
        const Api::Size& size
    ) -> void;
};


} // namespace
