#pragma once
#include "Core/Rect.h"
#include "Widgets/Widget/Widget.h"


namespace Blade {


class ApiWidget
{
public:
    virtual ~ApiWidget() = default;


    virtual auto setRect(const Rect& rect) -> void = 0;

    virtual auto name() const -> std::string { return "ApiWidget"; }

    virtual auto show() -> void = 0;

    virtual auto hide() -> void = 0;

    auto addChild(std::unique_ptr<ApiWidget> child) -> void
    {
        m_children.push_back(
            std::move(child)
        );
    }

    virtual auto create(ApiWidget& parent) -> void = 0;

    virtual auto create() -> void
    {
    }

    auto createChildren() -> void
    {
        for (auto& child : m_children)
        {
            child->create(*this);
            child->createChildren();
        }
    }

protected:
    ApiWidget* m_parent = nullptr;
    std::vector<std::unique_ptr<ApiWidget>> m_children;
};


} // namespace
