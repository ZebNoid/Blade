#include "Button.h"


namespace Blade {


auto Button::type() const -> Api::Text
{
    return L"Button";
}

auto Button::buildTree() const -> Api::WidgetTree
{
    Api::WidgetTree node;

    node.id = m_id;
    node.type = type();
    node.props = m_text;

    return node;
}

} // namespace
