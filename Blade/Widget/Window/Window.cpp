#include "Window.h"


namespace Blade {

//
// Window::Window(std::unique_ptr<Widget> child)
//     : m_child(std::move(child))
// {
// }
//
// auto Window::type() const -> Api::Text
// {
//     return L"Window";
// }
//
// auto Window::buildTree() const -> Api::WidgetTree
// {
//     Api::WidgetTree node;
//
//     node.id = m_id;
//     node.type = type();
//
//     if (m_child)
//     {
//         node.children.push_back(m_child->buildTree());
//     }
//
//     return node;
// }

} // namespace
