#pragma once

#include "Base/Widget.h"
#include "RowProps.h"
#include "Runtime/Normalize/Normalize.h"


namespace Blade {

class Row : public Widget<Row>
{
public:
    Row()
    {
        m_tree.type = Api::WidgetTypes::Row;
        m_tree.layoutType = LayoutType::Row;
        Normalize::PropsMerge(m_tree, RowProps{});
    }

    template <typename... TChildren>
    explicit Row(TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::Row;
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

};

} // namespace Blade
