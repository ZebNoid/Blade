#pragma once

#include <functional>
#include <optional>

#include "Command/ElementCommand.h"
#include "Common/ComponentType.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {

class NativeFactoryRegistry
{
public:
    using Factory = std::function<std::optional<NativeNode>(const Api::ElementCommand&)>;

    auto add(Api::ComponentType type, Factory factory) -> void;

    auto create(Api::ComponentType type, const Api::ElementCommand& command) -> std::optional<NativeNode>;

private:
    std::unordered_map<Api::ComponentType, Factory> m_factories;
};

} // namespace Blade::Backend
