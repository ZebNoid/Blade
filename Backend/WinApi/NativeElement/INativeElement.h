#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {


class INativeElement
{
public:
    virtual ~INativeElement() = default;

    virtual auto handle() const -> HWND = 0;

    virtual auto applyProps(const Api::PropertyMap&) -> void = 0;

    virtual auto applyEvents(const Api::EventSubscriptions&) -> void = 0;

    // TODO for all or only for window?
    virtual auto isAlive() const -> bool = 0;
    virtual auto isLifetimeOwner() const -> bool = 0;

    virtual auto attachChild(INativeElement* child) -> void = 0;
};


} // namespace
