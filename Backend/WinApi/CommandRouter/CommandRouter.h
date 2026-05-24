#pragma once

#include "Common/Property.h"
#include "Common/Types.h"


namespace Blade::Backend {

class CommandRouter
{
public:
    auto on(
        Api::Id id,
        Api::CallbackVoid callback
    ) -> void;

    auto dispatch(
        WPARAM wParam,
        LPARAM lParam
    ) -> bool;

private:
    std::unordered_map<Api::Id, Api::CallbackVoid> m_handlers;
};

} // namespace Blade::Backend
