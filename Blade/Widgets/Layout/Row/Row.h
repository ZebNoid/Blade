#pragma once


#include "Widgets/Widget/Widget.h"
#include "Widgets/Layout/Container/Container.h"
#include "Props/Widget/RowProps.h"

class Row : public Container
{
public:
    Row() = default;

    template <typename... T>
    Row(T&&... widgets)
    {
        (m_children.push_back(std::make_unique<std::decay_t<T>>(
                std::forward<T>(widgets))
        ), ...);
    }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override
    {
        for (const auto& child : m_children)
        {
            child->mount(m, ctx);
        }
    }

    auto measure(Size available) -> Size override;
    auto arrange(Rect rect) -> void override;

    auto set(RowProps props) -> Row&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

protected:
    RowProps m_props;
};
