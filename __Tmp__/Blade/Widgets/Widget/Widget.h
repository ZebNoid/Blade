#pragma once

#include <memory>

#include "Core/Core.h"
#include "Events/WidgetEvent/WidgetEvent.h"
#include "WidgetsProps/LayoutProps/LayoutProps.h"
#include "WidgetsProps/Common/Size.h"


namespace Blade {


enum class WidgetEvent;


class Widget
{
public:
    Widget() = default;

    virtual ~Widget() = default;

    Widget(const Widget&) = delete;

    auto operator=(const Widget&) -> Widget& = delete;

    Widget(Widget&&) = default;

    auto operator=(Widget&&) -> Widget& = default;

    virtual auto name() -> std::wstring = 0;

    virtual auto measure(Size available) -> Size = 0;

    virtual auto arrange(const Rect rect) -> void
    {
        m_rect = rect;
    }

    auto layout() const -> const LayoutProps&
    {
        return m_layout;
    }

    auto rect() const -> const Rect&
    {
        return m_rect;
    }


    auto children() -> const auto&
    {
        return m_children;
    }

protected:
    auto add(std::unique_ptr<Widget> child) -> void
    {
        m_children.push_back(std::move(child));
    }

    template <typename TWidget>
    auto addWidget(TWidget&& widget) -> void
    {
        static_assert(
            !std::is_lvalue_reference_v<TWidget>,
            "Widgets are move-only"
        );

        add(std::make_unique<std::decay_t<TWidget>>(
                std::forward<TWidget>(widget))
        );
    }

protected:
    std::vector<std::unique_ptr<Widget>> m_children;

    WidgetId m_id = -1;
    Rect m_rect{};
    LayoutProps m_layout;
};


} // namespace
