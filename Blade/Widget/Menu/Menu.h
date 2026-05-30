#pragma once

#include "Base/Widget.h"
#include "Menu/MenuTrigger.h"

namespace Blade {

class Menu : public Widget<Menu>
{
public:
    Menu()
    {
        m_tree.type = Api::WidgetTypes::Menu;
        m_tree.layoutType = LayoutType::Virtual;
        trigger(Api::MenuTrigger::RightClick);
    }

    template <typename... TChildren>
    explicit Menu(TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::Menu;
        m_tree.layoutType = LayoutType::Virtual;
        trigger(Api::MenuTrigger::RightClick);

        (
            m_tree.children.push_back(children.tree()),
            ...
        );
    }

    auto trigger(Api::MenuTrigger trigger) -> Menu&
    {
        m_tree.backend.create[Api::Props::MenuTrigger] = trigger;
        return *this;
    }
};

} // namespace Blade
