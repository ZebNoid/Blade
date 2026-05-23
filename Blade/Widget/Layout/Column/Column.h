#pragma once


#include "ColumnProps.h"
#include "Common/LayoutProps.h"
#include "Widget/Layout/Container.h"


namespace Blade {

class Column : public Container
{
public:
    Column() = default;

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        (
            add(
                std::forward<TChildren>(children)
            ),
            ...
        );
    }

    // TODO ColumnProps
    auto set(ColumnProps props) -> Column&
    {
        // TODO
        // m_tree.layout = Normalize::Layout(props);
        m_tree.props = Normalize::Props(props);
        return *this;
    }

    auto type() const -> Api::Text override
    {
        return L"Column";
    }

    auto buildTree() const
        -> WidgetTree override
    {
        WidgetTree tree;

        tree.type = type();

        buildChildren(tree);

        return tree;
    }
};


} // namespace
