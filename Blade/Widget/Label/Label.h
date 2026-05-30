#pragma once

#include "Base/Widget.h"

namespace Blade {

class Label : public Widget<Label>
{
public:
    explicit Label(Api::Text text)
    {
        m_tree.type = Api::WidgetTypes::Label;
        size({120, 24});
        m_tree.backend.create[Api::Props::Title] = std::move(text);
    }

    auto text(Api::Text value) -> Label&
    {
        m_tree.backend.create[Api::Props::Title] = std::move(value);
        return *this;
    }

};

} // namespace Blade
