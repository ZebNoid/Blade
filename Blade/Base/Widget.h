#pragma once

#include "Base/WidgetNode.h"


namespace Blade {


template <typename TSelf>
class Widget : public WidgetNode
{
public:
    Widget() = default;

    explicit Widget(WidgetTree tree)
        : WidgetNode(std::move(tree))
    {
    }

    auto modifier(const Api::Modifier& modifier) -> TSelf&
    {
        this->m_tree.modifier.append(modifier);

        for (const auto& op : modifier.ops())
        {
            this->applyModifier(op);
        }

        return self();
    }

    auto padding(Api::Thickness value) -> TSelf&
    {
        return modifier(Api::Modifier().padding(value));
    }

    auto padding(int value) -> TSelf&
    {
        return padding(Api::Thickness{value});
    }

    auto background(Api::Color value) -> TSelf&
    {
        return modifier(Api::Modifier().background(value));
    }

    auto borderRadius(int value) -> TSelf&
    {
        return modifier(Api::Modifier().borderRadius(value));
    }

    auto borderColor(Api::Color value) -> TSelf&
    {
        return modifier(Api::Modifier().borderColor(value));
    }

    auto color(Api::Color value) -> TSelf&
    {
        return modifier(Api::Modifier().color(value));
    }

    auto states(const Api::ModifierStates& value) -> TSelf&
    {
        return modifier(Api::Modifier().states(value));
    }

    auto size(Api::Size value) -> TSelf&
    {
        this->applySize(value);
        return self();
    }

    auto flex(int value) -> TSelf&
    {
        this->applyFlex(value);
        return self();
    }

    auto visible(bool value = true) -> TSelf&
    {
        this->applyVisible(value);
        return self();
    }

private:
    auto self() -> TSelf&
    {
        return static_cast<TSelf&>(*this);
    }
};


} // namespace
