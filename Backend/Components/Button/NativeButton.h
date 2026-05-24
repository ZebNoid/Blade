#pragma once

#include "WinApi/INativeElement/INativeElement.h"


namespace Blade::Backend {

class NativeWindow;

class NativeButton : public INativeElement
{
public:
    auto create(NativeWindow* parent, Api::Id id) -> bool;

    auto handle() const -> HWND override;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto applyEvents(const Api::EventSubscriptions& events) -> void override;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override
    {
    }

private:
    HWND m_hwnd = nullptr;
    Api::Id m_id = Api::InvalidId;
    NativeWindow* m_parent = nullptr;
};


} // namespace
