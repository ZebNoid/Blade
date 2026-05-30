#pragma once

#include "Base/Widget.h"
#include "MenuProps.h"
#include "Runtime/Normalize/Normalize.h"

namespace Blade {

class Menu : public Widget<Menu>
{
public:
    Menu()
    {
        m_tree.type = L"Menu";
        m_tree.layoutType = LayoutType::Virtual;
        Normalize::PropsMerge(m_tree, MenuProps{});
    }

    template <typename... TChildren>
    explicit Menu(TChildren&&... children)
    {
        m_tree.type = L"Menu";
        m_tree.layoutType = LayoutType::Virtual;
        Normalize::PropsMerge(m_tree, MenuProps{});

        (
            m_tree.children.push_back(children.tree()),
            ...
        );
    }

    auto set(MenuProps props) -> Menu&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }

    auto trigger(Api::MenuTrigger trigger) -> Menu&
    {
        m_tree.backend.create[Api::Props::MenuTrigger] = trigger;
        return *this;
    }
};

} // namespace Blade
