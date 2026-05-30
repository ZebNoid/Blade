#include "ResourceManager.h"

#include <algorithm>

#include "WinApi/Render/RenderApi/RenderApi.h"
#include "WinApi/Resource/FontApi/FontApi.h"
#include "WinApi/Theme/ThemeApi/ThemeApi.h"

namespace Blade::Backend {

namespace {

auto ColorKey(Api::Color color) -> std::uint32_t
{
    const auto r = static_cast<std::uint32_t>(std::clamp(color.r, 0, 255));
    const auto g = static_cast<std::uint32_t>(std::clamp(color.g, 0, 255));
    const auto b = static_cast<std::uint32_t>(std::clamp(color.b, 0, 255));
    const auto a = static_cast<std::uint32_t>(std::clamp(color.a, 0, 255));
    return r | (g << 8) | (b << 16) | (a << 24);
}

auto PenKey(Api::Color color, int width) -> std::uint64_t
{
    const auto safeWidth = width < 1 ? 1 : width;
    return static_cast<std::uint64_t>(ColorKey(color)) | (static_cast<std::uint64_t>(safeWidth) << 32);
}

auto ToGdiPlusColor(Api::Color color) -> Gdiplus::Color
{
    return {
        static_cast<BYTE>(std::clamp(color.a, 0, 255)),
        static_cast<BYTE>(std::clamp(color.r, 0, 255)),
        static_cast<BYTE>(std::clamp(color.g, 0, 255)),
        static_cast<BYTE>(std::clamp(color.b, 0, 255))
    };
}

} // namespace

ResourceManager::~ResourceManager()
{
    if (m_defaultFontOwned) FontApi::Destroy(m_defaultFont);
    for (const auto& [_, brush] : m_brushes) DeleteObject(brush);
    for (const auto& [_, pen] : m_pens) DeleteObject(pen);
}

auto ResourceManager::defaultFont() -> HFONT
{
    if (!m_defaultFont)
    {
        m_defaultFont = FontApi::CreateMessageFont();
        m_defaultFontOwned = m_defaultFont != nullptr;
    }

    if (!m_defaultFont) m_defaultFont = FontApi::DefaultGuiFont();

    return m_defaultFont;
}

auto ResourceManager::windowBrush() -> HBRUSH
{
    return ThemeApi::WindowBrush();
}

auto ResourceManager::windowTextColor() -> COLORREF
{
    return ThemeApi::WindowTextColor();
}

auto ResourceManager::brush(Api::Color color) -> HBRUSH
{
    const auto key = ColorKey(color);
    if (const auto it = m_brushes.find(key); it != m_brushes.end()) return it->second;

    auto handle = CreateSolidBrush(RenderApi::ToColorRef(color));
    m_brushes[key] = handle;
    return handle;
}

auto ResourceManager::pen(Api::Color color, int width) -> HPEN
{
    const auto key = PenKey(color, width);
    if (const auto it = m_pens.find(key); it != m_pens.end()) return it->second;

    const auto safeWidth = width < 1 ? 1 : width;
    auto handle = CreatePen(PS_SOLID, safeWidth, RenderApi::ToColorRef(color));
    m_pens[key] = handle;
    return handle;
}

auto ResourceManager::gdiPlusBrush(Api::Color color) -> Gdiplus::SolidBrush*
{
    const auto key = ColorKey(color);
    if (const auto it = m_gdiPlusBrushes.find(key); it != m_gdiPlusBrushes.end()) return it->second.get();

    auto brush = std::make_unique<Gdiplus::SolidBrush>(ToGdiPlusColor(color));
    auto* handle = brush.get();
    m_gdiPlusBrushes[key] = std::move(brush);
    return handle;
}

auto ResourceManager::gdiPlusPen(Api::Color color, int width) -> Gdiplus::Pen*
{
    const auto key = PenKey(color, width);
    if (const auto it = m_gdiPlusPens.find(key); it != m_gdiPlusPens.end()) return it->second.get();

    const auto safeWidth = width < 1 ? 1 : width;
    auto pen = std::make_unique<Gdiplus::Pen>(ToGdiPlusColor(color), static_cast<Gdiplus::REAL>(safeWidth));
    auto* handle = pen.get();
    m_gdiPlusPens[key] = std::move(pen);
    return handle;
}

auto ResourceManager::image(const Api::Text& path) -> Gdiplus::Image*
{
    if (path.empty()) return nullptr;
    if (const auto it = m_images.find(path); it != m_images.end()) return it->second.get();

    auto image = std::make_unique<Gdiplus::Image>(path.c_str());
    if (!image || image->GetLastStatus() != Gdiplus::Ok)
    {
        // TODO change: add explicit resource cache invalidation when runtime reload is supported.
        m_images[path] = nullptr;
        return nullptr;
    }

    auto* handle = image.get();
    m_images[path] = std::move(image);
    return handle;
}

} // namespace Blade::Backend
