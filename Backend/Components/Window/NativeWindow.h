#pragma once

#include "WinApi/Router/CommandRouter/CommandRouter.h"
#include "WinApi/Router/MessageRouter/MessageRouter.h"
#include "WinApi/NativeElement/NativeElement.h"


namespace Blade::Backend {


class NativeWindow : public NativeElement
{
public:
    auto create(HINSTANCE hInstance) -> bool;

    auto applyEvents(const Api::EventSubscriptions& events) -> void override;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override;

    // TODO for all?
    auto show(int cmdShow = SW_SHOW) -> void;

    auto router() -> MessageRouter&;

    auto commandRouter() -> CommandRouter&;

    auto destroy() -> void;
    auto markDead() -> void;

private:
    bool m_alive = true;

    MessageRouter m_router;
    CommandRouter m_commandRouter;
};


} // namespace
