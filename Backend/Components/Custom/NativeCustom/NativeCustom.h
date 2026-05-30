#pragma once

#include <optional>

#include "Common/Modifier.h"
#include "Common/Rect.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "WinApi/NativeElement/NativeElement.h"

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
    auto updateRegion(const Api::Rect& rect, int radius) -> void;

private:
    ResourceManager* m_resources = nullptr;
    RenderRegistry* m_renderNodes = nullptr;
    bool m_trackingMouse = false;
    bool m_hovered = false;
    bool m_pressed = false;
    bool m_focused = false;
    Api::Size m_regionSize{};
    int m_regionRadius = 0;
};

} // namespace Blade::Backend
