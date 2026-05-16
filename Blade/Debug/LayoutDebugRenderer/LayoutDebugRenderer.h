#pragma once

#include <windows.h>

#include "Widgets/Widget/Widget.h"


namespace Blade {

/// Legend
///
/// Red - widget bounds
/// Green - padding
/// Orange - margin

class LayoutDebugRenderer
{
public:
    // TODO toggle and force redraw
    static bool debug;

    static auto Render(HDC hdc, Widget& widget) -> void;

    virtual auto children() -> const std::vector<std::unique_ptr<Widget>>&;
};


} // namespace
