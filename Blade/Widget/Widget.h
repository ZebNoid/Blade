#pragma once
#include <memory>
#include <vector>

#include "Common/Common.h"
#include "Props/LayoutProps.h"


namespace Blade {


class Widget
{
public:
    // --- move only ---
    Widget() = default;

    virtual ~Widget() = default;

    Widget(const Widget&) = delete;
    auto operator=(const Widget&) -> Widget& = delete;

    Widget(Widget&&) = default;
    auto operator=(Widget&&) -> Widget& = default;

    // --- Widget interface ---
    virtual auto name() const -> Api::Text = 0;

    auto id() const -> Api::Id
    {
        return m_id;
    }

    // --- Widget children ---
    auto add(std::unique_ptr<Widget> child) -> void
    {
        m_children.push_back(std::move(child));
    }

    auto children() const
        -> const std::vector<std::unique_ptr<Widget>>&
    {
        return m_children;
    }

protected:
    Api::Id m_id = 0;

    LayoutProps m_layout;

    std::vector<std::unique_ptr<Widget>> m_children;
};


} // namespace
