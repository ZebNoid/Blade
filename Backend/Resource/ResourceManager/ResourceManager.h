#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include <windows.h>
#include <gdiplus.h>

#include "Common/Types.h"
#include "Style/Color.h"

namespace Blade::Backend {

class ResourceManager
{
public:
    ~ResourceManager();

    ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    auto operator=(const ResourceManager&) -> ResourceManager& = delete;
    ResourceManager(ResourceManager&&) = delete;
    auto operator=(ResourceManager&&) -> ResourceManager& = delete;

    auto defaultFont() -> HFONT;
    auto windowBrush() -> HBRUSH;
    auto windowTextColor() -> COLORREF;
    auto brush(Api::Color color) -> HBRUSH;
    auto pen(Api::Color color, int width = 1) -> HPEN;
    auto gdiPlusBrush(Api::Color color) -> Gdiplus::SolidBrush*;
    auto gdiPlusPen(Api::Color color, int width = 1) -> Gdiplus::Pen*;
    auto image(const Api::Text& path) -> Gdiplus::Image*;

private:
    HFONT m_defaultFont = nullptr;
    bool m_defaultFontOwned = false;
    std::unordered_map<std::uint32_t, HBRUSH> m_brushes;
    std::unordered_map<std::uint64_t, HPEN> m_pens;
    std::unordered_map<std::uint32_t, std::unique_ptr<Gdiplus::SolidBrush>> m_gdiPlusBrushes;
    std::unordered_map<std::uint64_t, std::unique_ptr<Gdiplus::Pen>> m_gdiPlusPens;
    std::unordered_map<Api::Text, std::unique_ptr<Gdiplus::Image>> m_images;
};

} // namespace Blade::Backend
