#pragma once

#include "Common/Types.h"
#include "Runtime/Normalize/PropsVisitor.h"

namespace Blade {

struct TrayProps
{
    Api::Text title = L"Blade";
    Api::Text icon{};

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Title, title);
        v.set(Api::Props::Icon, icon);
    }
};

} // namespace Blade
