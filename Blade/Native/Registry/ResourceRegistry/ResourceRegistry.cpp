#include "ResourceRegistry.h"

auto ResourceRegistry::Init() -> void
{
    if (s_initialized) return;
    s_initialized = true;

    RegisterFont("system", CreateSystemUIFont());
}

auto ResourceRegistry::Shutdown() -> void
{
    for (auto& [key, font] : s_fonts)
    {
        if (font)
        {
            DeleteObject(font);
        }
    }

    s_fonts.clear();
}

auto ResourceRegistry::RegisterFont(const std::string& key, HFONT font) -> void
{
    if (!font) return;

    // already exists
    const auto it = s_fonts.find(key);

    if (it != s_fonts.end())
    {
        DeleteObject(it->second);
    }

    s_fonts[key] = font;
}

auto ResourceRegistry::GetFont(const std::string& key) -> HFONT
{
    auto it = s_fonts.find(key);

    if (it == s_fonts.end())
    {
        return nullptr;
    }

    return it->second;
}

auto ResourceRegistry::CreateSystemUIFont() -> HFONT
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
