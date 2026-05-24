#include "NativeElement.h"


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

} // namespace Blade::Backend
