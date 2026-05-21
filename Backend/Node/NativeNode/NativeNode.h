#pragma once

#include "Common/Types.h"


namespace Blade::Backend {


struct NativeNode
{
    Api::Id id = Api::InvalidId;

    Api::Text type;

    HWND hwnd = nullptr;
};


} // namespace
