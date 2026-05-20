#include "Window.h"


namespace Blade {


Window::Window(Widget child)
    : m_child(std::move(child))
{
}

auto Window::set(WindowProps props) -> Window&
{
    m_props = std::move(props);
    return *this;
}

auto Window::on(WindowEvents events) -> Window&
{
    m_events = std::move(events);
    return *this;
}

auto Window::type() const -> Api::Text
{
    return L"Window";
}

auto Window::buildTree() const -> Api::WidgetTree
{
    Api::WidgetTree node;

    node.id = m_id;
    node.type = type();

    node.props = m_props;
    node.events = m_events;

    if (m_child.has_value())
    {
        node.children.push_back(m_child->buildTree());
    }

    return node;
}


} // namespace
