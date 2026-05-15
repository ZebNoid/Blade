#include "ResourceRegistry.h"

auto ResourceRegistry::init() -> void
{
    if (m_sInitialized) return;
    m_sInitialized = true;

    register_font("system", create_system_ui_font());
}

auto ResourceRegistry::shutdown() -> void
{
    for (auto& [key, font] : m_sFonts)
    {
        if (font)
        {
            DeleteObject(font);
        }
    }

    m_sFonts.clear();
}

auto ResourceRegistry::register_font(const std::string& key, HFONT font) -> void
{
    if (!font) return;

    // already exists
    const auto it = m_sFonts.find(key);

    if (it != m_sFonts.end())
    {
        DeleteObject(it->second);
    }

    m_sFonts[key] = font;
}

auto ResourceRegistry::get_font(const std::string& key) -> HFONT
{
    auto it = m_sFonts.find(key);

    if (it == m_sFonts.end())
    {
        return nullptr;
    }

    return it->second;
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
