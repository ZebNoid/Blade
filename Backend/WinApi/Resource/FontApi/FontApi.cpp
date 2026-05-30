#include "FontApi.h"

namespace Blade::Backend {

auto FontApi::CreateMessageFont() -> HFONT
{
    NONCLIENTMETRICSW metrics{};
    metrics.cbSize = sizeof(metrics);

    if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0)) return nullptr;

    return CreateFontIndirectW(&metrics.lfMessageFont);
}

auto FontApi::DefaultGuiFont() -> HFONT
{
    return static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
}

auto FontApi::Destroy(HFONT font) -> void
{
    if (font) DeleteObject(font);
}

} // namespace Blade::Backend
