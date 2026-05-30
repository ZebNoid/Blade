#pragma once

#include "Geometry/Rect.h"
#include "Menu/MenuData.h"
#include "Render/RenderOp.h"
#include "WinApi/NativeElement/NativeElement.h"

namespace Blade::Backend {

class NativeWindow;
class RenderRegistry;
class ResourceManager;
struct NativeCreateContext;

class NativeLabel : public NativeElement
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
    auto mouseDown(RenderRegistry& renderNodes) -> bool;
    auto mouseUp(RenderRegistry& renderNodes) -> bool;
    auto focus(RenderRegistry& renderNodes, bool focused) -> bool;

private:
    Api::Text m_text;
    Api::Rect m_rect{};
    bool m_visible = true;
    bool m_emitClick = false;
    bool m_emitFocus = false;
    bool m_emitDrop = false;
    bool m_pressed = false;
    bool m_focused = false;
    Api::ContextMenus m_contextMenus;
};

} // namespace Blade::Backend
