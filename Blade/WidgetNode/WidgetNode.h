#pragma once
#include "Api/WidgetTree.h"


namespace Blade {


class WidgetNode
{
public:
    WidgetNode() = default;

    template <typename T>
    WidgetNode(T widget)
        : m_tree(widget.buildTree())
    {
    }

    template <typename... TWidgets>
    WidgetNode(TWidgets&&... widgets)
    {
        (add(std::forward<TWidgets>(widgets)), ...);
    }

    auto tree() const -> Api::WidgetTree
    {
        return m_tree;
    }

// private:
    void add(auto&& widget)
    {
        m_tree.children.push_back(widget.buildTree());
    }

private:
    Api::WidgetTree m_tree;
};

} // namespace
