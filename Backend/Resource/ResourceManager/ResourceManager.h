#pragma once

#include <cstdint>
#include <unordered_map>

#include <windows.h>

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

private:
    HFONT m_defaultFont = nullptr;
    bool m_defaultFontOwned = false;
    std::unordered_map<std::uint32_t, HBRUSH> m_brushes;
    std::unordered_map<std::uint64_t, HPEN> m_pens;
};

} // namespace Blade::Backend
