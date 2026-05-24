#pragma once

#include <unordered_map>

#include "Api/ApiBackend.h"
#include "Base/WidgetTree.h"


namespace Blade {

class EventRuntime
{
public:
    auto registerTree(const WidgetTree& tree) -> void;

    auto dispatch(const Api::BackendEvent& event) -> Api::EventResult;

private:
    std::unordered_map<Api::Id, Api::EventMap> m_events;
};

} // namespace Blade
