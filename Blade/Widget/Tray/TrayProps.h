#pragma once

#include "Lifecycle/Lifetime.h"
#include "Common/Types.h"
#include "Runtime/Normalize/PropsVisitor.h"

namespace Blade {

struct TrayProps
{
    Api::Text title = L"Blade";
    Api::Text icon{};
    Api::Lifetime lifetime = Api::Lifetime::Owner;

    auto visit(PropsVisitor& v) const -> void
    {
        v.set(Api::Props::Title, title);
        v.set(Api::Props::Icon, icon);
        v.set(Api::Props::Lifetime, lifetime);
    }
};

} // namespace Blade
