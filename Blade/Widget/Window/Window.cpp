#include "Window.h"


namespace Blade {

auto Window::buildTree() const -> Api::WidgetTree
{
    Api::WidgetTree node;

    node.type = type();
    node.id = m_id;

    for (auto& child : m_children)
    {
        node.children.push_back(child->buildTree());
    }

    return {
        .id = m_id,
        .type = type(),
    };
}

} // namespace
