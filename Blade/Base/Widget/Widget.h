#pragma once


namespace Blade {


class Widget
{
public:
    Widget() = default;

    Widget(Api::WidgetTree tree)
        : m_tree(std::move(tree))
    {
    }

    auto buildTree() const -> Api::WidgetTree
    {
        return m_tree;
    }

protected:
    Api::WidgetTree m_tree;
};


} // namespace
