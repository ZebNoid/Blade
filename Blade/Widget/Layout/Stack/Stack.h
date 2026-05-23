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
        Normalize::PropsMerge(m_tree, StackProps{});
    }

    template <typename... TChildren>
    explicit Stack(TChildren&&... children)
    {
        m_tree.type = L"Stack";
        m_tree.layoutType = LayoutType::Stack;
        Normalize::PropsMerge(m_tree, StackProps{});

        (
            m_tree.children.push_back(
                children.tree()
            ),
            ...
        );
    }

    auto set(StackProps props) -> Stack&
    {
        Normalize::PropsMerge(m_tree, props);
        return *this;
    }
};

} // namespace Blade
