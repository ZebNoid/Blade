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
        Normalize::PropsMerge(m_tree, ColumnProps{});
    }

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        m_tree.type = L"Column";
        m_tree.layoutType = LayoutType::Column;
        Normalize::PropsMerge(m_tree, ColumnProps{});

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(ColumnProps props) -> Column&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto gap(int gap) -> Column&
    {
        m_tree.layout.gap = gap;
        return *this;
    }

    auto flex(int flex) -> Column&
    {
        applyFlex(flex);
        return *this;
    }

    auto padding(Api::Thickness padding) -> Column&
    {
        applyPadding(padding);
        return *this;
    }

};


} // namespace
