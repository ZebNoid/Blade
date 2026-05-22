#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {


class INativeElement
{
public:
    virtual ~INativeElement() = default;

    virtual auto handle() const -> HWND = 0;

    virtual auto applyProps(
        const Api::PropertyMap&
    ) -> void = 0;

    virtual auto applyEvents(
        const Api::EventMap&
    ) -> void = 0;

    virtual auto isAlive() const -> bool = 0;
};


} // namespace