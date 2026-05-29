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
    auto registerTree(const WidgetTree& tree, Api::Id parent) -> void;
    auto hasHandler(Api::Id target, Api::Events event) const -> bool;
    auto dispatchNode(Api::Id target, const Api::BackendEvent& event, Api::EventContext& context) -> Api::EventResult;
    auto parentOf(Api::Id target) const -> Api::Id;

private:
    std::unordered_map<Api::Id, Api::EventMap> m_events;
    std::unordered_map<Api::Id, Api::Id> m_parents;
};

} // namespace Blade
