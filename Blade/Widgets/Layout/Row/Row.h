#pragma once

#include "WidgetsProps/Widget/RowProps.h"
#include "Widgets/Layout/Container/Container.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class Row : public Widget
{
public:
    Row() = default;

    template <typename... T>
    Row(T&&... widgets)
    {
        (addWidget(
            std::forward<T>(widgets)
        ), ...);

        // (m_children.push_back(std::make_unique<std::decay_t<T>>(
        //         std::forward<T>(widgets))
        // ), ...);
    }

    auto name() -> std::wstring override { return L"Row"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override
    {
        for (const auto& child : m_children)
        {
            child->mount(m, ctx);
        }
    }

    auto measure(Size available) -> Size override;

    auto arrange(Rect rect) -> void override;

    auto set(RowProps props) & -> Row&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto set(RowProps props) && -> Row&&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return std::move(*this);
    }

protected:
    RowProps m_props;
};


} // namespace
