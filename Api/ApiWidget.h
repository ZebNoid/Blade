#pragma once
#include <memory>
#include <vector>

#include "Data/CommonTypes.h"


namespace Blade::Api {


class ApiWidget
{
public:
    virtual ~ApiWidget() = default;

    // --- lifecycle ---
    virtual auto show() -> void = 0;

    virtual auto hide() -> void = 0;

    virtual auto destroy() -> void = 0;

    // --- geometry ---
    virtual auto setRect(const Rect& rect) -> void = 0;

    // --- identity ---
    auto id() const -> Id { return m_id; }

    // --- children (backend-side tree mirror) ---
    auto addChild(std::unique_ptr<ApiWidget> child) -> void
    {
        m_children.push_back(std::move(child));
    }

    auto& children() const { return m_children; }

protected:
    BladeId m_id = 0;

    std::vector<std::unique_ptr<ApiWidget>> m_children;
};


} // namespace
