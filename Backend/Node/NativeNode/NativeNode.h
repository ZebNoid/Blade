#pragma once

#include <windows.h>

#include "Common/Types.h"
#include "WinApi/INativeElement/INativeElement.h"


namespace Blade::Backend {


struct NativeNode
{
    Api::Id id = Api::InvalidId;

    Api::Text type;

    Api::Id parent = Api::InvalidId;

    std::unique_ptr<INativeElement> native;
};


} // namespace
