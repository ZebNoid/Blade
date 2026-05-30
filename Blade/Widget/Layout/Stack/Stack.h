#pragma once

#include "Base/Widget.h"


namespace Blade {

class Stack : public Widget<Stack>
{
public:
    Stack()
    {
        m_tree.type = Api::WidgetTypes::Stack;
        m_tree.layoutType = LayoutType::Stack;
    }

    template <typename... TChildren>
    explicit Stack(TChildren&&... children)
    {
        m_tree.type = Api::WidgetTypes::Stack;
        m_tree.layoutType = LayoutType::Stack;

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

};

} // namespace Blade
