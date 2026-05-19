#pragma once

#include "Api/ApiWidget.h"
#include "Widgets/Widget/Widget.h"


namespace Blade::Backend {


class Materializer
{
public:
    auto create(Widget& widget) -> std::unique_ptr<ApiWidget>;

    auto mount(Widget& root) -> std::unique_ptr<ApiWidget>;

    auto buildChildren(Widget& widget, ApiWidget& native) -> void;

    auto syncLayout(Widget& widget) -> void;

private:
    std::unordered_map<Widget*, ApiWidget*> m_widgets;
};


} // namespace
