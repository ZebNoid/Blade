#pragma once


#include "ColumnProps.h"


namespace Blade {

class Column : public Widget
{
public:
    Column() = default;

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        m_tree.type = Column::type();

        (
            m_tree.children.push_back(
                children.buildTree()
            ),
            ...
        );
    }

    // TODO ColumnProps
    auto set(ColumnProps props) -> Column&
    {
        m_tree.props = Normalize::Props(props);
        return *this;
    }

    auto type() const -> Api::Text override
    {
        return L"Column";
    }

    // auto buildTree() const
    //     -> WidgetTree override
    // {
    //     WidgetTree tree;
    //
    //     tree.type = type();
    //
    //     buildChildren(tree);
    //
    //     return tree;
    // }
};


} // namespace
