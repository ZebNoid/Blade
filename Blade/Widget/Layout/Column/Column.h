#pragma once

#include "Base/Widget.h"
#include "Props/LayoutProps/CrossAxisAlignment.h"
#include "Props/LayoutProps/MainAxisAlignment.h"


namespace Blade {

class Column : public Widget<Column>
{
public:
    Column()
    {
        m_tree.type = Api::WidgetTypes::Column;
        m_tree.layoutType = LayoutType::Column;
    }

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::Column;
        m_tree.layoutType = LayoutType::Column;

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto gap(int gap) -> Column&
    {
        m_tree.layout.gap = gap;
        return *this;
    }

    auto mainAxisAlignment(MainAxisAlignment alignment) -> Column&
    {
        m_tree.layout.mainAxisAlignment = alignment;
        return *this;
    }

    auto crossAxisAlignment(CrossAxisAlignment alignment) -> Column&
    {
        m_tree.layout.crossAxisAlignment = alignment;
        return *this;
    }

    auto verticalAlignment(MainAxisAlignment alignment) -> Column&
    {
        return mainAxisAlignment(alignment);
    }

    auto horizontalAlignment(CrossAxisAlignment alignment) -> Column&
    {
        return crossAxisAlignment(alignment);
    }

};


} // namespace
