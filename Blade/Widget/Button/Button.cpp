#include "Button.h"


namespace Blade {

Button::Button(Api::Text text)
    : m_text(std::move(text))
{
}

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
