#include "GdiPlusScope.h"

namespace Blade::Backend {

GdiPlusScope::~GdiPlusScope()
{
    if (m_token) Gdiplus::GdiplusShutdown(m_token);
}

auto GdiPlusScope::init() -> void
{
    if (m_token) return;

    Gdiplus::GdiplusStartupInput input{};
    Gdiplus::GdiplusStartup(&m_token, &input, nullptr);
}

auto GdiPlusScope::ready() const -> bool
{
    return m_token != 0;
}

} // namespace Blade::Backend
