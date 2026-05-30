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
};

} // namespace Blade
