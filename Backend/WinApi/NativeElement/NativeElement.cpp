#include "NativeElement.h"

#include "WinApi/HwndApi/HwndApi.h"

namespace Blade::Backend {

auto NativeElement::handle() const -> HWND
{
    return m_hwnd;
}

auto NativeElement::id() const -> Api::Id
{
    return m_id;
}

auto NativeElement::parent() const -> NativeElement*
{
    return m_parent;
}

auto NativeElement::isLifetimeOwner() const -> bool
{
    return m_lifetimeOwner;
}

auto NativeElement::destroy() -> void
{
    if (m_hwnd)
    {
        HwndApi::Destroy(m_hwnd);
        m_hwnd = nullptr;
    }
}

} // namespace Blade::Backend
