#pragma once

#include "Base/Widget.h"

namespace Blade {

class ContextArea : public Widget
{
public:
    template <typename TContent, typename... TMenus>
    explicit ContextArea(TContent&& content, TMenus&&... menus)
    {
        m_tree.type = L"ContextArea";
        m_tree.layoutType = LayoutType::Virtual;
        m_tree.children.push_back(content.tree());

        (
            m_tree.overlays.push_back(menus.tree()),
            ...
        );
    }
};

} // namespace Blade
