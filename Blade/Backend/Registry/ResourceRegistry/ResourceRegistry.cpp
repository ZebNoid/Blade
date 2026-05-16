#include "ResourceRegistry.h"


namespace Blade {


auto ResourceRegistry::Init() -> void
{
    if (m_sInitialized) return;
    m_sInitialized = true;

    RegisterFont("system", create_system_ui_font());
}

auto ResourceRegistry::Shutdown() -> void
{
    for (auto& [key, font] : m_fonts)
    {
        if (!font)continue;
        DeleteObject(font);
    }

    m_fonts.clear();

    for (auto& [key, pen] : m_pens)
    {
        if (!pen) continue;
        DeleteObject(pen);
    }

    m_pens.clear();
}

auto ResourceRegistry::RegisterFont(const std::string& key, HFONT font) -> void
{
    if (!font) return;

    // already exists
    const auto it = m_fonts.find(key);

    if (it != m_fonts.end())
    {
        DeleteObject(it->second);
    }

    m_fonts[key] = font;
}

auto ResourceRegistry::GetFont(const std::string& key) -> HFONT
{
    auto it = m_fonts.find(key);

    if (it == m_fonts.end())
    {
        return nullptr;
    }

    return it->second;
}

auto ResourceRegistry::GetPen(const std::string& key, COLORREF color, int width) -> HPEN
{
    auto it = m_pens.find(key);
    if (it != m_pens.end()) return it->second;

    HPEN pen = CreatePen(PS_SOLID, width, color);
    m_pens[key] = pen;

    return pen;
}

auto ResourceRegistry::create_system_ui_font() -> HFONT
{
    NONCLIENTMETRICSW ncm{};
    ncm.cbSize = sizeof(ncm);

    SystemParametersInfoW(
        SPI_GETNONCLIENTMETRICS,
        sizeof(ncm),
        &ncm,
        0
    );

    return CreateFontIndirectW(&ncm.lfMessageFont);
}


} // namespace
