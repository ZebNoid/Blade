#pragma once

#include <windows.h>

#include "Common/Property.h"


namespace Blade::Backend {


class NativeButton
{
public:
    auto create(HWND parent) -> bool;

    auto handle() const -> HWND;

    auto applyProps(
        const Api::PropertyMap& propertyMap
    ) -> void;

    auto applyEvents(
        const Api::EventMap& eventMap
    ) -> void;

private:
    HWND m_hwnd = nullptr;
};


} // namespace
