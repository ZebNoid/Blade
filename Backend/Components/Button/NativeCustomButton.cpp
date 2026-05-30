#include "NativeCustomButton.h"

namespace Blade::Backend {

auto NativeCustomButton::hitTest() const -> LRESULT
{
    return HTCLIENT;
}

} // namespace Blade::Backend
