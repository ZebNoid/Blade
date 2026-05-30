#pragma once

#include "Base/Widget.h"
#include "Props/LayoutProps/CrossAxisAlignment.h"
#include "Props/LayoutProps/MainAxisAlignment.h"


namespace Blade {

class Row : public Widget<Row>
{
public:
    Row()
    {
        m_tree.type = Api::WidgetTypes::Row;
        m_tree.layoutType = LayoutType::Row;
    }

    template <typename... TChildren>
    explicit Row(TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::Row;
        m_tree.layoutType = LayoutType::Row;

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto gap(int gap) -> Row&
    {
        m_tree.layout.gap = gap;
        return *this;
    }

    auto mainAxisAlignment(MainAxisAlignment alignment) -> Row&
    {
        m_tree.layout.mainAxisAlignment = alignment;
        return *this;
    }

    auto crossAxisAlignment(CrossAxisAlignment alignment) -> Row&
    {
        m_tree.layout.crossAxisAlignment = alignment;
        return *this;
    }

    auto horizontalAlignment(MainAxisAlignment alignment) -> Row&
    {
        return mainAxisAlignment(alignment);
    }

    auto verticalAlignment(CrossAxisAlignment alignment) -> Row&
    {
        return crossAxisAlignment(alignment);
    }

};

} // namespace Blade
