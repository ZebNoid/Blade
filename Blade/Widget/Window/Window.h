#pragma once
#include "Widget/Widget.h"


namespace Blade {


class Window : public Widget
{
public:
    Window() = default;

    template <typename TWidget>
    Window(TWidget child)
    {
        add(std::move(child));
    }

    auto type() const -> Api::Text override { return L"Window"; }

    auto buildTree() const -> Api::WidgetTree override;
};


} // namespace
