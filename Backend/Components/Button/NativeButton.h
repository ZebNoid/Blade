#pragma once

#include "WinApi/NativeElement/NativeElement.h"


namespace Blade::Backend {

class NativeWindow;

class NativeButton : public NativeElement
{
public:
    auto create(NativeWindow* parent, Api::Id id) -> bool;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto applyEvents(const Api::EventSubscriptions& events) -> void override;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override
    {
    }

};


} // namespace
