#pragma once

#include "Base/Widget.h"
#include "MenuItemEvents.h"
#include "MenuItemProps.h"

namespace Blade {

class MenuItem : public Widget<MenuItem>
{
public:
    explicit MenuItem(Api::Text text)
    {
        m_tree.type = Api::WidgetTypes::MenuItem;
        m_tree.layoutType = LayoutType::Virtual;
        m_tree.backend.create[Api::Props::Title] = std::move(text);
        Normalize::PropsMerge(m_tree, MenuItemProps{});
    }

    template <typename... TChildren>
    explicit MenuItem(Api::Text text, TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::MenuItem;
        m_tree.layoutType = LayoutType::Virtual;
        m_tree.backend.create[Api::Props::Title] = std::move(text);
        Normalize::PropsMerge(m_tree, MenuItemProps{});

        (
            m_tree.children.push_back(children.tree()),
            ...
        );
    }

    auto set(MenuItemProps props) -> MenuItem&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto on(MenuItemEvents events) -> MenuItem&
    {
        m_tree.events = Normalize::Events(events);
        return *this;
    }

    auto shortcut(Api::Shortcut shortcut) -> MenuItem&
    {
        m_tree.backend.create[Api::Props::Shortcut] = shortcut;
        return *this;
    }

    auto onClick(Api::EventCallback callback) -> MenuItem&
    {
        applyEvent(Api::Events::Click, std::move(callback));
        return *this;
    }
};

} // namespace Blade
