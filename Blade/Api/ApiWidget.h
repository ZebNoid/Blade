#pragma once
#include "Core/Rect.h"


namespace Blade {

class ApiWidget
{
public:
    virtual ~ApiWidget() = default;

    virtual auto create(ApiWidget& parent) -> void = 0;

    virtual auto setRect(const Rect& rect) -> void = 0;

    virtual auto show() -> void = 0;

    virtual auto hide() -> void = 0;

    auto addChild(std::unique_ptr<ApiWidget> child) -> void
    {
        m_children.push_back(
            std::move(child)
        );
    }

    auto createChildren() -> void
    {
        for (auto& child : m_children)
        {
            child->create(*this);
        }
    }

protected:
    ApiWidget* m_parent = nullptr;
    std::vector<std::unique_ptr<ApiWidget>> m_children;
};


} // namespace
