#pragma once

#include "Base/Widget.h"
#include "ContextAreaEvents.h"
#include "Runtime/Normalize/Normalize.h"

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

    auto on(ContextAreaEvents events) -> ContextArea&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};

} // namespace Blade
