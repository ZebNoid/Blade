#include "NativeLabel.h"

#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

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
    if (node) RenderApi::Draw(hdc, rect, node->render.forState(node->state));

    const auto color = node ? RenderApi::TextColor(node->render.forState(node->state), resourceManager->windowTextColor()) : resourceManager->windowTextColor();
    RenderApi::Text(hdc, m_text, rect, resourceManager->defaultFont(), color);
}

auto NativeLabel::hitTest() const -> LRESULT
{
    return renderNodes() && renderNodes()->get(id()) ? HTCLIENT : HTTRANSPARENT;
}

} // namespace Blade::Backend
