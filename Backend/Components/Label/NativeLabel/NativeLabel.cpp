#include "NativeLabel.h"

#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

namespace {

auto HasBackground(const Api::RenderDefinition& render) -> bool
{
    for (const auto& op : render.ops)
    {
        if (std::holds_alternative<Api::RenderBackground>(op)) return true;
    }

    return false;
}

auto HasBackground(const Api::RenderStates& render) -> bool
{
    return HasBackground(render.normal)
        || HasBackground(render.hover)
        || HasBackground(render.focus)
        || HasBackground(render.pressed)
        || HasBackground(render.disabled)
        || HasBackground(render.dragOver);
}

} // namespace

auto NativeLabel::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    if (const auto* text = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Title)) m_text = *text;
    NativeCustom::applyProps(propertyMap);
}

auto NativeLabel::onPaint(HDC hdc, const Api::Rect& rect) -> void
{
    auto* resourceManager = resources();
    if (!resourceManager) return;

    const auto* node = renderNodes() ? renderNodes()->get(id()) : nullptr;
    if (node) GdiPlusRenderApi::Draw(hdc, rect, node->render.forState(node->state), *resourceManager);

    const auto color = node ? RenderApi::TextColor(node->render.forState(node->state), resourceManager->windowTextColor()) : resourceManager->windowTextColor();
    RenderApi::Text(hdc, m_text, rect, resourceManager->defaultFont(), color);
}

auto NativeLabel::hitTest() const -> LRESULT
{
    return renderNodes() && renderNodes()->get(id()) ? HTCLIENT : HTTRANSPARENT;
}

auto NativeLabel::exStyle() const -> DWORD
{
    const auto* node = renderNodes() ? renderNodes()->get(id()) : nullptr;
    // TODO change: transparent labels over sibling HWNDs require proper render surfaces/layers.
    return node && HasBackground(node->render) ? 0 : WS_EX_TRANSPARENT;
}

} // namespace Blade::Backend
