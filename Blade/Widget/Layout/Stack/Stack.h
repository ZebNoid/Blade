#pragma once

#include "Base/Widget.h"
#include "Runtime/Normalize/Normalize.h"
#include "StackProps.h"


namespace Blade {

class Stack : public Widget
{
public:
    Stack()
    {
        m_tree.type = L"Stack";
        m_tree.layoutType = LayoutType::Stack;
        m_tree.props = Normalize::Props(StackProps{});
    }

    template <typename... TChildren>
    explicit Stack(TChildren&&... children)
    {
        m_tree.type = L"Stack";
        m_tree.layoutType = LayoutType::Stack;
        m_tree.props = Normalize::Props(StackProps{});

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(StackProps props) -> Stack&
    {
        Normalize::PropsMerge(m_tree.props, props);
        return *this;
    }
};

} // namespace Blade
