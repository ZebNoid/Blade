#pragma once

#include <windows.h>
#include <gdiplus.h>

namespace Blade::Backend {

class GdiPlusScope
{
public:
    ~GdiPlusScope();

    GdiPlusScope() = default;
    GdiPlusScope(const GdiPlusScope&) = delete;
    auto operator=(const GdiPlusScope&) -> GdiPlusScope& = delete;
    GdiPlusScope(GdiPlusScope&&) = delete;
    auto operator=(GdiPlusScope&&) -> GdiPlusScope& = delete;

    auto init() -> void;
    auto ready() const -> bool;

private:
    ULONG_PTR m_token = 0;
};

} // namespace Blade::Backend
