#pragma once

#include "WinApi/NativeElement/INativeElement.h"


namespace Blade::Backend {

class NativeElement : public INativeElement
{
public:
    auto handle() const -> HWND override;
    auto id() const -> Api::Id;
    auto parent() const -> NativeElement*;

protected:
    HWND m_hwnd = nullptr;
    Api::Id m_id = Api::InvalidId;
    NativeElement* m_parent = nullptr;
};

} // namespace Blade::Backend
