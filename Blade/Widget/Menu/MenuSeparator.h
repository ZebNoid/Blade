#pragma once

#include "Base/Widget.h"

namespace Blade {

class MenuSeparator : public Widget<MenuSeparator>
{
public:
    MenuSeparator()
    {
        m_tree.type = L"MenuSeparator";
        m_tree.layoutType = LayoutType::Virtual;
    }
};

} // namespace Blade
