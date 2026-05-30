#pragma once

#include "Base/Widget.h"
#include "Menu/Shortcut.h"

namespace Blade {

class MenuItem : public Widget<MenuItem>
{
public:
    explicit MenuItem(Api::Text text)
    {
        m_tree.type = Api::WidgetTypes::MenuItem;
        m_tree.layoutType = LayoutType::Virtual;
        m_tree.backend.create[Api::Props::Title] = std::move(text);
        shortcut(Api::Shortcut::None());
    }

    template <typename... TChildren>
    explicit MenuItem(Api::Text text, TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::MenuItem;
        m_tree.layoutType = LayoutType::Virtual;
        m_tree.backend.create[Api::Props::Title] = std::move(text);
        shortcut(Api::Shortcut::None());

        (
            m_tree.children.push_back(children.tree()),
            ...
        );
    }

    auto shortcut(Api::Shortcut shortcut) -> MenuItem&
    {
        m_tree.backend.create[Api::Props::Shortcut] = shortcut;
        return *this;
    }

};

} // namespace Blade
