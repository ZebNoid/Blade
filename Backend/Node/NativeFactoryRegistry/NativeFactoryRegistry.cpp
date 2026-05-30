#include "NativeFactoryRegistry.h"


namespace Blade::Backend {

auto NativeFactoryRegistry::add(Api::WidgetType type, Factory factory) -> void
{
    m_factories.insert_or_assign(type, std::move(factory));
}

auto NativeFactoryRegistry::create(const Api::ElementCommand& command) -> std::optional<NativeNode>
{
    const auto it = m_factories.find(command.nodeType);
    return it == m_factories.end() ? std::nullopt : it->second(command);
}

} // namespace Blade::Backend
