#pragma once

#include "Widget/WinWidget/WinWidget.h"
#include "Widgets/Widget/Widget.h"


namespace Blade::Backend {


class Materializer
{
public:
    auto create(Widget& widget) -> std::unique_ptr<WinWidget>;

    auto mount(Widget& root) -> WinWidget*;

    // auto registerWidget(
    //     Widget& widget,
    //     ApiWidget& native
    // ) -> void;
    //
    // // find()
    // auto native(
    //     Widget& widget
    // ) -> ApiWidget*;
    //
    // auto unregisterWidget(
    //     Widget& widget
    // ) -> void;
    //
    //
    // // TODO to WinWindow
    // // TODO no WidgetContext!
    // auto mount(Widget& widget, WidgetContext& ctx) -> void
    // {
    //     // TODO mount
    //     // widget.mount(*this, ctx);
    // }

private:
    std::unordered_map<Widget*, WinWidget*> m_widgets;
};


} // namespace
