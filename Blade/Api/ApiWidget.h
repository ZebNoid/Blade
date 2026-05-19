#pragma once
#include "Core/Rect.h"


namespace Blade {

class ApiWidget
{
public:
    virtual ~ApiWidget() = default;

    virtual auto setRect(const Rect& rect) -> void = 0;

    virtual auto show() -> void = 0;

    virtual auto hide() -> void = 0;

};


} // namespace
