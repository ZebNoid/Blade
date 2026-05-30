#pragma once

#include "Common/Callbacks.h"
#include "Base/WidgetTree.h"


namespace Blade {


class Widget
{
public:
    Widget() = default;

    explicit Widget(WidgetTree tree)
        : m_tree(std::move(tree))
    {
    }

    auto tree() const -> const WidgetTree&
    {
        return m_tree;
    }

protected:
    auto applySize(Api::Size size) -> void
    {
        m_tree.layout.size = size;
        m_tree.backend.create[Api::Props::Size] = size;
    }

    auto applyFlex(int flex) -> void
    {
        m_tree.layout.box.flex = flex;
    }

    auto applyPadding(Api::Thickness padding) -> void
    {
        m_tree.layout.box.padding = padding;
    }

    auto applyVisible(bool visible) -> void
    {
        m_tree.backend.create[Api::Props::Visible] = visible;
    }

    auto applyEvent(Api::Events event, Api::EventCallback callback) -> void
    {
        if (callback) m_tree.events[event] = callback.value();
    }

protected:
    WidgetTree m_tree;
};


} // namespace
