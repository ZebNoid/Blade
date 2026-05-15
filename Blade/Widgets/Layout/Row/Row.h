#pragma once


#include "../../Widget/Widget.h"
#include "../Container/Container.h"

class Row : public Container
{
public:
    Row() = default;

    template <typename... T>
    Row(T&&... widgets)
    {
        (m_children.push_back(std::make_unique<std::decay_t<T>>(
                std::forward<T>(widgets))
        ), ...);
    }

    auto mount(Materializer& m, WidgetContext& ctx) -> void override
    {
        for (const auto& child : m_children)
        {
            child->mount(m, ctx);
        }
    }

    auto measure(Size available) -> Size override;
    auto arrange(Rect rect) -> void override;
};
