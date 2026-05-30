#pragma once

#include "Base/Widget.h"


namespace Blade {

class Button : public Widget<Button>
{
public:
    explicit Button(Api::Text text)
    {
        m_tree.type = Api::WidgetTypes::Button;
        size({100, 50});
        defaultButton(false);
        m_tree.backend.create[Api::Props::Title] = std::move(text);
    }

    auto defaultButton(bool value = true) -> Button&
    {
        m_tree.backend.create[Api::Props::IsDefault] = value;
        return *this;
    }

};

} // namespace
