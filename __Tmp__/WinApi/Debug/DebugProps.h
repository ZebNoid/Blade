#pragma once
#include "DebugBrushProps.h"


namespace Blade::Backend {


struct DebugProps
{
    DebugBrushProps bounds = {
        .color = "#00A500",
        .width = 1,
    };

    DebugBrushProps margin = {
        .color = "",
        .width = 1,
    };

    DebugBrushProps padding = {
        .color = "#00A5FF",
        .width = 1,
    };

    std::string textColor = "#00A500";
};


} // namespace
