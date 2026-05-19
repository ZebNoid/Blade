#pragma once


#include "WidgetsProps/Widget/StackProps.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class Stack : public Widget
{
public:
    Stack() = default;

    template <typename... T>
    Stack(T&&... widgets)
    {
        (addWidget(
            std::forward<T>(widgets)
        ), ...);
    }

    auto name() -> std::wstring override { return L"Stack"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override
    {
        for (const auto& child : m_children)
        {
            child->mount(m, ctx);
        }
    }

    auto measure(Size available) -> Size override;

    auto arrange(Rect rect) -> void override;

    auto set(StackProps props) & -> Stack&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto set(StackProps props) && -> Stack&&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return std::move(*this);
    }

protected:
    StackProps m_props;
};


} // namespace
