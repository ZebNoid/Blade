#pragma once

#include "Base/RootWidget.h"
#include "TrayEvents.h"
#include "TrayProps.h"
#include "Runtime/Normalize/Normalize.h"

namespace Blade {

class Tray : public RootWidget
{
public:
    Tray()
    {
        m_tree.type = L"Tray";
        Normalize::PropsMerge(m_tree, TrayProps{});
    }

    template <typename... TMenus>
    explicit Tray(TMenus&&... menus)
    {
        m_tree.type = L"Tray";
        Normalize::PropsMerge(m_tree, TrayProps{});

        (
            m_tree.overlays.push_back(menus.tree()),
            ...
        );
    }

    auto set(TrayProps props) -> Tray&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto on(TrayEvents events) -> Tray&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }
};

} // namespace Blade
