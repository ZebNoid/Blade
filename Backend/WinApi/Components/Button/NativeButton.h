#pragma once

#include "WinApi/INativeElement/INativeElement.h"


namespace Blade::Backend {


class NativeButton : public INativeElement
{
public:
    auto create(HWND parent) -> bool;

    auto handle() const -> HWND override;

    auto applyProps(
        const Api::PropertyMap& propertyMap
    ) -> void override;

    auto applyEvents(
        const Api::EventMap& eventMap
    ) -> void override;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override
    {
    }

private:
    HWND m_hwnd = nullptr;
};


} // namespace
