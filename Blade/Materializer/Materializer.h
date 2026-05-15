#pragma once

#include "../Widgets/Widget/Widget.h"


class Materializer
{
public:
    auto mount(Widget& widget, WidgetContext& ctx) -> void
    {
        // TODO auto bind context or Modifier?
        widget.mount(*this, ctx);
    }
};
