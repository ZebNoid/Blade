#pragma once

#include "Context/WidgetContext.h"
#include "Core/Core.h"
#include "Events/WidgetEvent/WidgetEvent.h"
#include "Props/Common/LayoutProps.h"
#include "Props/Common/Size.h"


namespace Blade {


enum class WidgetEvent;


class Widget
{
public:
    virtual ~Widget() = default;

    virtual auto name() -> std::wstring = 0;

    virtual auto mount(class Materializer& m, struct WidgetContext& ctx) -> void = 0;

    virtual auto measure(Size available) -> Size = 0;

    virtual auto arrange(const Rect rect) -> void
    {
        m_rect = rect;
    }

    auto layout() const -> const LayoutProps&
    {
        return m_layout;
    }

    auto rect() -> Rect
    {
        return m_rect;
    }

    virtual auto children() -> const std::vector<std::unique_ptr<Widget>>&
    {
        static std::vector<std::unique_ptr<Widget>> empty; // TODO why?
        return empty;
    }

protected:
    static auto allocateId(const WidgetContext& ctx) -> WidgetId;

    auto bindEvent(const WidgetContext& ctx, WidgetEvent event, const EventHandler& fn) const -> void;

protected:
    WidgetId m_id = -1;
    Rect m_rect{};
    LayoutProps m_layout;
};


} // namespace
