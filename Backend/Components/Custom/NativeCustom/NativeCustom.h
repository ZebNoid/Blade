#pragma once

#include <optional>

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
    virtual auto hitTest() const -> LRESULT;
    auto resources() const -> ResourceManager*;
    auto renderNodes() const -> RenderRegistry*;

private:
    static auto CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
    auto handle(UINT msg, WPARAM wParam, LPARAM lParam) -> std::optional<LRESULT>;

private:
    ResourceManager* m_resources = nullptr;
    RenderRegistry* m_renderNodes = nullptr;
};

} // namespace Blade::Backend
