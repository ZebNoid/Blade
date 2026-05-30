#include "NativeLabel.h"

#include "Property/PropertyReader.h"
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

    RenderApi::Text(hdc, m_text, rect, resourceManager->defaultFont(), resourceManager->windowTextColor());
}

auto NativeLabel::hitTest() const -> LRESULT
{
    return HTTRANSPARENT;
}

} // namespace Blade::Backend
