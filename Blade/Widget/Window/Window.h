#pragma once

#include <optional>

#include "WindowProps.h"
#include "WindowEvents.h"
#include "Widget/Widget.h"
#include "WidgetNode/WidgetNode.h"


namespace Blade {

class Window : public Widget
{
public:
    Window() = default;

    explicit Window(Widget child);

    auto set(WindowProps props) -> Window&;

    auto on(WindowEvents events) -> Window&;

    auto type() const -> Api::Text override;

    auto buildTree() const -> Api::WidgetTree override;

private:
    std::optional<std::unique_ptr<Widget>> m_child;

    WindowProps m_props{};
    WindowEvents m_events{};
};


} // namespace
