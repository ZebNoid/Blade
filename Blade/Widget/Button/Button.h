#pragma once
#include "Widget/Widget.h"


namespace Blade {


class Button : public Widget
{
public:
    explicit Button(Api::Text text);

    auto type() const -> Api::Text override;

    auto buildTree() const -> Api::WidgetTree override;

private:
    Api::Text m_text;
};

} // namespace
