#pragma once


#include <windows.h>
#include "Common/Types.h"


namespace Blade::Backend {


struct NativeNode
{
    Api::Id id = Api::InvalidId;

    Api::Text type;

    HWND hwnd = nullptr;

    Api::Id parent = Api::InvalidId;
};


} // namespace
