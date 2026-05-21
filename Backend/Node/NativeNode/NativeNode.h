#pragma once
#include "Common/Types.h"


namespace Blade::Backend {


struct NativeNode
{
    Api::Id id;

    Api::Text type;

    HWND hwnd = nullptr;
};


} // namespace
