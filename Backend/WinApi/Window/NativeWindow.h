#pragma once

#include "WinApi/INativeElement/INativeElement.h"
#include "WinApi/MessageRouter/MessageRouter.h"


namespace Blade::Backend {


class NativeWindow : public INativeElement
{
public:
    auto create(HINSTANCE hInstance) -> bool;

    auto handle() const -> HWND override;

    auto applyEvents(const Api::EventMap& eventMap) -> void override;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override;

    auto show(int cmdShow = SW_SHOW) -> void;

    auto router() -> MessageRouter&;

    auto destroy() -> void;
    auto markDead() -> void;

private:
    HWND m_hwnd = nullptr;
    bool m_alive = true;

    MessageRouter m_router;
};


} // namespace
