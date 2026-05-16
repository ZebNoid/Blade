#pragma once

#include "Widgets/Widget/Widget.h"


namespace Blade {


class Materializer
{
public:
    auto mount(Widget& widget, WidgetContext& ctx) -> void
    {
        widget.mount(*this, ctx);
    }
};


} // namespace
