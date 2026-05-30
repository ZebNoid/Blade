#pragma once

#include <optional>

#include "Common/Modifier.h"
#include "Geometry/Rect.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "WinApi/Menu/NativeContextMenu/NativeContextMenu.h"
#include "WinApi/NativeElement/NativeElement.h"
#include "WinApi/OleDragDrop/OleDropTarget/OleDropTarget.h"

namespace Blade::Backend {

class NativeWindow;
class ResourceManager;
class RenderRegistry;

class NativeCustom : public NativeElement
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
    auto hover(RenderRegistry& renderNodes, bool hovered) -> bool;
    auto dragOver(RenderRegistry& renderNodes, bool active) -> bool;
    auto mouseDown(RenderRegistry& renderNodes) -> bool;
    auto mouseUp(RenderRegistry& renderNodes) -> bool;
    auto focus(RenderRegistry& renderNodes, bool focused) -> bool;

protected:
    virtual auto onPaint(HDC hdc, const Api::Rect& rect) -> void;
    virtual auto exStyle() const -> DWORD;
    virtual auto hitTest() const -> LRESULT;
    auto resources() const -> ResourceManager*;
    auto renderNodes() const -> RenderRegistry*;

private:
    static auto CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
    auto handle(UINT msg, WPARAM wParam, LPARAM lParam) -> std::optional<LRESULT>;
    auto trackMouseLeave() -> void;
    auto updateRenderState(Api::WidgetState state) -> void;
    auto currentRenderState() const -> Api::WidgetState;
    auto updateState(RenderRegistry& renderNodes) -> bool;
    auto updateRegion(const Api::Rect& rect, int radius) -> void;
    auto emit(Api::Events event, Api::EventPayload payload = {}) -> void;
    auto enableDropTarget() -> void;
    auto enableContextMenus(Api::ContextMenus menus) -> void;

private:
    ResourceManager* m_resources = nullptr;
    RenderRegistry* m_renderNodes = nullptr;
    std::unique_ptr<OleDropTarget> m_dropTarget;
    std::unique_ptr<NativeContextMenu> m_contextMenu;
    Api::Rect m_rect{};
    bool m_visible = true;
    bool m_emitDrop = false;
    bool m_emitClick = false;
    bool m_emitFocus = false;
    bool m_trackingMouse = false;
    bool m_hovered = false;
    bool m_pressed = false;
    bool m_focused = false;
    bool m_dragOver = false;
    Api::ContextMenus m_contextMenus;
    Api::Size m_regionSize{};
    int m_regionRadius = 0;
};

} // namespace Blade::Backend
