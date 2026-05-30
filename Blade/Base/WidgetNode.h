#pragma once

#include "Common/Callbacks.h"
#include "Common/Modifier.h"
#include "Base/WidgetTree.h"

namespace Blade {

class WidgetNode
{
public:
    WidgetNode() = default;

    explicit WidgetNode(WidgetTree tree)
        : m_tree(std::move(tree))
    {
    }

    auto tree() const -> const WidgetTree&
    {
        return m_tree;
    }

protected:
    auto applyModifier(const Api::ModifierOp& op) -> void
    {
        std::visit([this](const auto& modifier) { applyModifier(modifier); }, op);
    }

    auto applyModifier(const Api::PaddingModifier&) -> void
    {
    }

    auto applyModifier(const Api::BackgroundModifier&) -> void
    {
    }

    auto applyModifier(const Api::BorderRadiusModifier&) -> void
    {
    }

    auto applyModifier(const Api::BorderColorModifier&) -> void
    {
    }

    auto applyModifier(const Api::TextColorModifier&) -> void
    {
    }

    auto applyModifier(const Api::SizeModifier& modifier) -> void
    {
        m_tree.layout.size = modifier.value;
        m_tree.backend.create[Api::Props::Size] = modifier.value;
    }

    auto applyModifier(const Api::FlexModifier& modifier) -> void
    {
        m_tree.layout.box.flex = modifier.value;
    }

    auto applyModifier(const Api::VisibleModifier& modifier) -> void
    {
        m_tree.backend.create[Api::Props::Visible] = modifier.value;
    }

    auto applyModifier(const Api::StateModifiers&) -> void
    {
    }

    auto applyEvent(Api::Events event, Api::EventCallback callback) -> void
    {
        if (callback) m_tree.events[event] = callback.value();
    }

protected:
    WidgetTree m_tree;
};

} // namespace Blade
