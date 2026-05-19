#pragma once

#include "Widget/WinWidget/ApiWidget.h"
#include "Widgets/Widget/Widget.h"


namespace Blade::Backend {


class Materializer
{
public:
    auto create(Widget& widget) -> std::unique_ptr<ApiWidget>;

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
    std::unordered_map<Widget*, ApiWidget*> m_widgets;
};


} // namespace
