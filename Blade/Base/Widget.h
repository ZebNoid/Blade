#pragma once


namespace Blade {


class Widget
{
public:
    virtual ~Widget() = default; // TODO ?

    Widget() = default;

    Widget(WidgetTree tree)
        : m_tree(std::move(tree))
    {
    }

    virtual auto type() const -> Api::Text
    {
        return L"Widget";
    }

    virtual auto buildTree() const -> WidgetTree
    {
        return m_tree;
    }

protected:
    WidgetTree m_tree;
};


} // namespace
