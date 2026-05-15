#pragma once

#include "../../Core/Core.h"
#include "../../Context/WidgetContext.h"
#include "../../Events/WidgetEvent/WidgetEvent.h"
#include "Props/Common/Size.h"

enum class WidgetEvent;

class Widget
{
public:
    virtual ~Widget() = default;

    virtual auto mount(class Materializer& m, struct WidgetContext& ctx) -> void = 0;

    virtual auto measure(Size available) -> Size = 0;

    virtual auto arrange(const Rect rect) -> void
    {
        m_rect = rect;
    }

protected:
    static auto allocateId(const WidgetContext& ctx) -> WidgetId;
    auto bindEvent(const WidgetContext& ctx, WidgetEvent event, const EventHandler& fn) const -> void;

protected:
    WidgetId m_id = -1;
    Rect m_rect{};

    // TODO as prop structure?
    // Thickness m_margin;
    // Thickness m_padding;
    //
    // Alignment m_horizontal;
    // Alignment m_vertical;
};
