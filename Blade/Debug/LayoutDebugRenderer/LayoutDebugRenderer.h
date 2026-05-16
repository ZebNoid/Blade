#pragma once

#include <windows.h>

#include "Widgets/Widget/Widget.h"


namespace Blade {


class LayoutDebugRenderer
{
public:
    static auto Render(
        HDC hdc,
        Widget& widget
    ) -> void;

    virtual auto children()
        -> const std::vector<std::unique_ptr<Widget>>&;
};


} // namespace
