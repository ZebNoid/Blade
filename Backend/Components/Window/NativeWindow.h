#pragma once

#include <memory>

#include "WinApi/NativeElement/NativeElement.h"
#include "WinApi/Menu/NativeContextMenu/NativeContextMenu.h"
#include "WinApi/OleDragDrop/OleDropTarget/OleDropTarget.h"
#include "WinApi/Router/CommandRouter/CommandRouter.h"
#include "WinApi/Router/MessageRouter/MessageRouter.h"


namespace Blade::Backend {


class NativeWindow : public NativeElement
{
public:
    auto create(HINSTANCE hInstance, Api::Id id) -> bool;

    auto applyEvents(const Api::EventSubscriptions& events) -> void override;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override;

    // TODO for all?
    auto show(int cmdShow = SW_SHOW) -> void;

    auto router() -> MessageRouter&;

    auto commandRouter() -> CommandRouter&;
    auto enableDropTarget() -> void;
    auto enableContextMenus(Api::ContextMenus menus) -> void;
    auto setLifetime(Api::Lifetime lifetime) -> void;

    auto setMinSize(const Api::Size& size) -> void;
    auto setMaxSize(const Api::Size& size) -> void;
    auto applyMinMax(MINMAXINFO* info) const -> void;

    auto destroy() -> void;
    auto markDead() -> void;

private:
    bool m_alive = true;
    Api::Size m_minSize{};
    Api::Size m_maxSize{};

    MessageRouter m_router;
    CommandRouter m_commandRouter;
    std::unique_ptr<OleDropTarget> m_dropTarget;
    std::unique_ptr<NativeContextMenu> m_contextMenu;
};


} // namespace
