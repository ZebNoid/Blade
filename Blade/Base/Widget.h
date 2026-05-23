#pragma once


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
    WidgetTree m_tree;
};


} // namespace
