#pragma once

#include "Geometry/Rect.h"
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

private:
    Api::Text m_text;
    Api::Rect m_rect{};
    bool m_visible = true;
};

} // namespace Blade::Backend
