#pragma once

#include "Geometry/Rect.h"
#include "Menu/MenuData.h"
#include "Render/RenderOp.h"
#include "Render/VirtualElementState/VirtualElementState.h"
#include "WinApi/NativeElement/NativeElement.h"

namespace Blade::Backend {

class NativeWindow;
class RenderRegistry;
class ResourceManager;
struct NativeCreateContext;

class LabelSurface : public NativeElement
{
public:
    auto create(NativeWindow* parent, Api::Id id, const NativeCreateContext& context) -> bool;
    auto applyProps(const Api::PropertyMap& propertyMap) -> void override;
    auto applyEvents(const Api::EventSubscriptions& events) -> void override;
    auto isAlive() const -> bool override;
    auto attachChild(INativeElement* child) -> void override;
    auto paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void;
    auto hitTest(Api::Point point) const -> bool;
    auto wantsDrop() const -> bool;
    auto hasContextMenu(Api::MenuTrigger trigger) const -> bool;
    auto showContextMenu(Api::MenuTrigger trigger, POINT screenPoint) -> bool;
    auto setState(RenderRegistry& renderNodes, Api::WidgetState state) -> bool;
    auto hover(RenderRegistry& renderNodes, bool hovered) -> bool;
    auto dragOver(RenderRegistry& renderNodes, bool active) -> bool;
    auto mouseDown(RenderRegistry& renderNodes) -> bool;
    auto mouseUp(RenderRegistry& renderNodes) -> bool;
    auto focus(RenderRegistry& renderNodes, bool focused) -> bool;

private:
    auto updateState(RenderRegistry& renderNodes) -> bool;

private:
    Api::Text m_text;
    Api::Rect m_rect{};
    VirtualElementEvents m_events;
    VirtualElementState m_state;
    Api::ContextMenus m_contextMenus;
};

} // namespace Blade::Backend
