#pragma once

#include "Common/Types.h"
#include "Widget/WidgetType.h"
#include "WinApi/NativeElement/INativeElement.h"


namespace Blade::Backend {


struct NativeNode
{
    Api::Id id = Api::InvalidId;

    Api::WidgetType type = Api::WidgetTypes::Unknown;

    Api::Id parent = Api::InvalidId;

    std::unique_ptr<INativeElement> native;
};


} // namespace
