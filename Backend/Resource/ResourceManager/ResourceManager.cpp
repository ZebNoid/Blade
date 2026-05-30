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

} // namespace Blade::Backend
