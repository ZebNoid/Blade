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
        auto normalized = Normalize::Props(props);
        for (auto& [key, value] : normalized)
        {
            m_tree.props.insert_or_assign(key, std::move(value));
        }
        return *this;
    }
};


} // namespace
