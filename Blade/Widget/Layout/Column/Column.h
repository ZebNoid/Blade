#pragma once

#include <memory>

#include "Api/WidgetTree.h"
#include "Common/LayoutProps.h"
#include "Widget/Layout/Container.h"


namespace Blade {

class Column : public Container
{
public:
    Column() = default;

    template <typename... TChildren>
    explicit Column(TChildren&&... children)
    {
        (
            add(
                std::forward<TChildren>(children)
            ),
            ...
        );
    }

    // TODO ColumnProps
    auto set(Api::LayoutProps props) -> Column&
    {
        m_layout = std::move(props);
        return *this;
    }

    auto type() const -> Api::Text override
    {
        return L"Column";
    }

    auto buildTree() const
        -> Api::WidgetTree override
    {
        Api::WidgetTree tree;

        tree.type = type();

        buildChildren(tree);

        return tree;

        // tree.props = Normalize::Props(m_layout);

        // for (const auto& child : m_children)
        // {
        //     tree.children.push_back(
        //         child->buildTree()
        //     );
        // }

        // return tree;
    }

private:
    Api::LayoutProps m_layout{};
};


} // namespace
