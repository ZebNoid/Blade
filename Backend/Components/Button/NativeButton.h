#pragma once

#include <memory>

#include "WinApi/NativeElement/NativeElement.h"
#include "WinApi/Menu/NativeContextMenu/NativeContextMenu.h"
#include "WinApi/OleDragDrop/OleDropTarget/OleDropTarget.h"


namespace Blade::Backend {

class NativeWindow;

class NativeButton : public NativeElement
{
public:
    auto create(NativeWindow* parent, Api::Id id) -> bool;

    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;

    auto applyEvents(const Api::EventSubscriptions& events) -> void override;
    auto enableDropTarget() -> void;
    auto enableContextMenus(Api::ContextMenus menus) -> void;

    auto isAlive() const -> bool override;

    auto attachChild(INativeElement* child) -> void override
    {
    }

private:
    std::unique_ptr<OleDropTarget> m_dropTarget;
    std::unique_ptr<NativeContextMenu> m_contextMenu;
};


} // namespace
