#include "ImageSurface.h"

#include <gdiplus.h>

#include "Property/PropertyReader.h"
#include "Resource/ResourceManager/ResourceManager.h"

namespace Blade::Backend {

auto ImageSurface::applyProps(const Api::PropertyMap& propertyMap) -> void
{
    RenderSurface::applyProps(propertyMap);
    if (const auto* source = PropertyReader::Get<Api::Text>(propertyMap, Api::Props::Source)) m_source = *source;
}

auto ImageSurface::paint(HDC hdc, ResourceManager& resources, RenderRegistry& renderNodes) -> void
{
    if (!visible()) return;

    RenderSurface::paint(hdc, resources, renderNodes);

    auto* image = resources.image(m_source);
    if (!image) return;

    const auto bounds = rect();
    if (bounds.width <= 0 || bounds.height <= 0) return;

    Gdiplus::Graphics graphics(hdc);
    graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
    graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
    graphics.DrawImage(image, bounds.x, bounds.y, bounds.width, bounds.height);
}

} // namespace Blade::Backend
