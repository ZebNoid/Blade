#pragma once


#include "ColumnProps.h"
#include "Runtime/Normalize/Normalize.h"


namespace Blade {

class Column : public Widget
{
public:
    Column()
    {
        m_tree.type = L"Column";
        m_tree.layoutType = LayoutType::Column;
        m_tree.props = Normalize::Props(ColumnProps{});
    }

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        m_tree.type = L"Column";
        m_tree.layoutType = LayoutType::Column;
        m_tree.props = Normalize::Props(ColumnProps{});

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(ColumnProps props) -> Column&
    {
        Normalize::PropsMerge(m_tree.props, props);
        return *this;
    }
};


} // namespace
