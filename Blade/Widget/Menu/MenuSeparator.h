#pragma once

#include "Base/Widget.h"

namespace Blade {

class MenuSeparator : public Widget<MenuSeparator>
{
public:
    MenuSeparator()
    {
        m_tree.type = Api::WidgetTypes::MenuSeparator;
        m_tree.layoutType = LayoutType::Virtual;
    }
};

} // namespace Blade
