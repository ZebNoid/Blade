#pragma once

#include "Base/Widget.h"
#include "MenuItemEvents.h"

namespace Blade {

class MenuItem : public Widget
{
public:
    explicit MenuItem(Api::Text text)
    {
        m_tree.type = L"MenuItem";
        m_tree.layoutType = LayoutType::Virtual;
        m_tree.backend.create[Api::Props::Title] = std::move(text);
    }

    auto on(MenuItemEvents events) -> MenuItem&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};

} // namespace Blade
