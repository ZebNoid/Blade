#pragma once

#include "Base/Widget.h"
#include "LabelProps.h"
#include "Runtime/Normalize/Normalize.h"

namespace Blade {

class Label : public Widget<Label>
{
public:
    explicit Label(Api::Text text)
    {
        m_tree.type = Api::WidgetTypes::Label;
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

};

} // namespace Blade
