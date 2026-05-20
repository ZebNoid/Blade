#pragma once
#include "Widget/Widget.h"


namespace Blade {


class Button : public Widget
{
public:
    Button(Api::Text text);

    auto type() const -> Api::Text override { return L"Button"; }
};


} // namespace
