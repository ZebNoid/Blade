#include "LabelSurface.h"

#include "Property/PropertyReader.h"
#include "Render/RenderRegistry/RenderRegistry.h"
#include "Resource/ResourceManager/ResourceManager.h"
#include "WinApi/Render/RenderApi/RenderApi.h"

namespace Blade::Backend {

auto LabelSurface::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    RenderSurface::applyProps(propertyMap);
    if (const auto* text = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Title)) m_text = *text;
}

auto LabelSurface::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!visible()) return;

    RenderSurface::paint(hdc, resources, renderNodes);

    const auto* node = renderNodes.get(m_id);
    const auto color = node ? RenderApi::TextColor(node->render.forState(node->state), resources.windowTextColor()) : resources.windowTextColor();
    RenderApi::Text(hdc, m_text, rect(), resources.defaultFont(), color);
}

} // namespace Blade::Backend
