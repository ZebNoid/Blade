#pragma once
#include <memory>
#include <vector>

#include "Common/Common.h"
#include "Props/LayoutProps.h"


namespace Blade {


class Widget
{
public:
    virtual ~Widget() = default;

    virtual auto type() const -> Api::Text = 0;

    virtual auto buildTree() const -> Api::WidgetTree = 0;

    auto id() const -> Api::Id { return m_id; }

protected:
    Api::Id m_id = 0;
};


} // namespace
