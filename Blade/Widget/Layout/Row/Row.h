#pragma once

#include "Base/Widget.h"
#include "RowProps.h"
#include "Runtime/Normalize/Normalize.h"


namespace Blade {

class Row : public Widget
{
public:
    Row()
    {
        m_tree.type = L"Row";
        m_tree.layoutType = LayoutType::Row;
        Normalize::PropsMerge(m_tree, RowProps{});
    }

    template <typename... TChildren>
    explicit Row(TChildren&&... children)
    {
        m_tree.type = L"Row";
        m_tree.layoutType = LayoutType::Row;
        Normalize::PropsMerge(m_tree, RowProps{});

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(RowProps props) -> Row&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto gap(int gap) -> Row&
    {
        m_tree.layout.gap = gap;
        return *this;
    }

    auto flex(int flex) -> Row&
    {
        applyFlex(flex);
        return *this;
    }

    auto padding(Api::Thickness padding) -> Row&
    {
        applyPadding(padding);
        return *this;
    }

};

} // namespace Blade
