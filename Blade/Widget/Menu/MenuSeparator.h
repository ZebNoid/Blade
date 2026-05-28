#pragma once

#include "Base/Widget.h"

namespace Blade {

class MenuSeparator : public Widget
{
public:
    MenuSeparator()
    {
        m_tree.type = L"MenuSeparator";
        m_tree.layoutType = LayoutType::Virtual;
    }
};

} // namespace Blade
