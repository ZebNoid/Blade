#pragma once


#include "../Widgets/Widget/Widget.h"

class Materializer
{
public:
    auto Mount(Widget& widget, WidgetContext& ctx) -> void
    {
        // TODO auto bind context or Modifier?
        widget.Mount(*this, ctx);
    }
};
