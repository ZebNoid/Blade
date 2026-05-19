#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "Widgets/Widget/Widget.h"


namespace Blade::Backend {


class Materializer
{
public:
    auto registerWidget(
        Widget& widget,
        WinWidget& native
    ) -> void;

    // find()
    auto native(
        Widget& widget
    ) -> WinWidget*;

    auto unregisterWidget(
        Widget& widget
    ) -> void;


    // TODO to WinWindow
    // TODO no WidgetContext!
    auto mount(Widget& widget, WidgetContext& ctx) -> void
    {
        // TODO mount
        // widget.mount(*this, ctx);
    }

private:
    std::unordered_map<Widget*, WinWidget*> m_widgets;
};


} // namespace
