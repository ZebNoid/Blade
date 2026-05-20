#pragma once
#include "Widget/Widget.h"


namespace Blade {


class Window : public Widget
{
public:
    Window();

    Window(std::unique_ptr<Widget> child);

    auto type() const -> Api::Text override;

    auto buildTree() const -> Api::WidgetTree override;

private:
    std::unique_ptr<Widget> m_child;
};


} // namespace
