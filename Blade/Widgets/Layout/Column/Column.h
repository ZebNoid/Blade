#pragma once

#include "WidgetsProps/Widget/ColumnProps.h"
#include "Widgets/Layout/Container/Container.h"


namespace Blade {


class Column : public Widget
{
public:
    Column() = default;

    template <typename... T>
    Column(T&&... widgets)
    {
        (addWidget(
            std::forward<T>(widgets)
        ), ...);
        // (add(
        //     std::make_unique<std::decay_t<T>>(
        //         std::forward<T>(widgets)
        //     )
        // ), ...);

        // (m_children.push_back(std::make_unique<std::decay_t<T>>(std::forward<T>(widgets))), ...);
    }

    auto name() -> std::wstring override { return L"Column"; }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override
    {
        for (const auto& child : m_children)
        {
            child->mount(m, ctx);
        }
    }

    auto measure(Size available) -> Size override;

    auto arrange(Rect rect) -> void override;

    auto set(ColumnProps props) & -> Column&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return *this;
    }

    auto set(ColumnProps props) && -> Column&&
    {
        m_layout = props.layout;
        m_props = std::move(props);
        return std::move(*this);
    }

protected:
    ColumnProps m_props;
};


} // namespace
