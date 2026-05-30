#pragma once

#include "Base/Widget.h"
#include "LabelProps.h"
#include "Runtime/Normalize/Normalize.h"

namespace Blade {

class Label : public Widget
{
public:
    explicit Label(Api::Text text)
    {
        m_tree.type = L"Label";
        Normalize::PropsMerge(m_tree, LabelProps{});
        m_tree.backend.create[Api::Props::Title] = std::move(text);
    }

    auto set(LabelProps props) -> Label&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto text(Api::Text value) -> Label&
    {
        m_tree.backend.create[Api::Props::Title] = std::move(value);
        return *this;
    }

    auto size(Api::Size size) -> Label&
    {
        applySize(size);
        return *this;
    }

    auto flex(int flex) -> Label&
    {
        applyFlex(flex);
        return *this;
    }

    auto padding(Api::Thickness padding) -> Label&
    {
        applyPadding(padding);
        return *this;
    }

    auto visible(bool visible) -> Label&
    {
        applyVisible(visible);
        return *this;
    }
};

} // namespace Blade
