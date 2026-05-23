#pragma once


#include "ColumnProps.h"


namespace Blade {

class Column : public Widget
{
public:
    Column()
    {
        m_tree.type = L"Column";
    }

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        m_tree.type = L"Column";

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(ColumnProps props) -> Column&
    {
        m_tree.props = Normalize::Props(props);
        return *this;
    }
};


} // namespace
