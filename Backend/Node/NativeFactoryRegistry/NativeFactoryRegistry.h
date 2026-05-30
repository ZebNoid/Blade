#pragma once

#include <functional>
#include <optional>

#include "Command/ElementCommand.h"
#include "Node/NativeNode/NativeNode.h"


namespace Blade::Backend {

class NativeFactoryRegistry
{
public:
    using Factory = std::function<std::optional<NativeNode>(const Api::ElementCommand&)>;

    auto add(Api::WidgetType type, Factory factory) -> void;

    auto create(const Api::ElementCommand& command) -> std::optional<NativeNode>;

private:
    std::unordered_map<Api::WidgetType, Factory> m_factories;
};

} // namespace Blade::Backend
