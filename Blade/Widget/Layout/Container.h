#pragma once

#include <memory>
#include <vector>

#include "Api/WidgetTree.h"
#include "Base/Widget.h"


namespace Blade {

class Container : public Widget
{
public:
    Container() = default;

protected:
    template <typename TWidget>
    auto add(TWidget&& widget) -> void
    {
        m_children.push_back(
            std::make_unique<std::decay_t<TWidget>>(
                std::forward<TWidget>(widget)
            )
        );
    }

    auto buildChildren(
        Api::WidgetTree& tree
    ) const -> void
    {
        for (const auto& child : m_children)
        {
            tree.children.push_back(
                child->buildTree()
            );
        }
    }

protected:
    std::vector<
        std::unique_ptr<Widget>
    > m_children;
};


} // namespace
