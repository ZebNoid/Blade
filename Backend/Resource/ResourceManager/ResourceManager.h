#pragma once

#include <windows.h>

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

private:
    HFONT m_defaultFont = nullptr;
    bool m_defaultFontOwned = false;
};

} // namespace Blade::Backend
