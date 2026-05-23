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
        m_tree.props = Normalize::Props(RowProps{});
    }

    template <typename... TChildren>
    explicit Row(TChildren&&... children)
    {
        m_tree.type = L"Row";
        m_tree.layoutType = LayoutType::Row;
        m_tree.props = Normalize::Props(RowProps{});

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(RowProps props) -> Row&
    {
        Normalize::PropsMerge(m_tree.props, props);
        return *this;
    }
};

} // namespace Blade
