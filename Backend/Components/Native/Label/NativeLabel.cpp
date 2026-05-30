#include "NativeLabel.h"

#include "Components/Window/NativeWindow.h"
#include "Node/NativeCreateContext/NativeCreateContext.h"
#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/HwndApi/HwndApi.h"
#include "WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

auto NativeLabel::create(NativeWindow* parent, Api::Id id, const NativeCreateContext&) -> bool
{
    if (!parent) return false;

    m_parent = parent;
    m_id = id;
    m_hwnd = parent->handle();
    return m_hwnd != nullptr;
}

auto NativeLabel::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* text = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Title)) m_text = *text;
    if (const auto* rect = PropertyReader::Get<Api::Rect>(propertyMap, Api::Props::Rect)) m_rect = *rect;
    if (const auto* visible = PropertyReader::Get<bool>(propertyMap, Api::Props::Visible)) m_visible = *visible;

    HwndApi::Invalidate(m_hwnd);
}

auto NativeLabel::applyEvents(const Api::EventSubscriptions&) -> void
{
}

auto NativeLabel::isAlive() const -> bool
{
    return true;
}

auto NativeLabel::attachChild(INativeElement*) -> void
{
}

auto NativeLabel::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!m_visible) return;

    const auto* node = renderNodes.get(m_id);
    if (node) GdiPlusRenderApi::Draw(hdc, m_rect, node->render.forState(node->state), resources);

    const auto color = node ? RenderApi::TextColor(node->render.forState(node->state), resources.windowTextColor()) : resources.windowTextColor();
    RenderApi::Text(hdc, m_text, m_rect, resources.defaultFont(), color);
}

} // namespace Blade::Backend
