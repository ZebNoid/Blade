#pragma once

#include <unordered_map>
#include <vector>

#include "Common/ComponentType.h"
#include "Common/Types.h"
#include "Common/WidgetType.h"

namespace Blade::Backend {

struct NativeBindingInfo
{
    Api::WidgetType widget = Api::WidgetTypes::Unknown;
    Api::ComponentType component = Api::ComponentTypes::Unknown;
};

struct ComponentInfo
{
    Api::ComponentType type = Api::ComponentTypes::Unknown;
    Api::Text name;
};

using NativeBindings = std::unordered_map<Api::WidgetType, Api::ComponentType>;

class NativeBindingRegistry
{
public:
    auto bind(Api::WidgetType widget, Api::ComponentType component) -> void;
    auto bind(const NativeBindings& bindings) -> void;
    auto resolve(Api::WidgetType widget) const -> Api::ComponentType;
    auto defaultBindings() const -> std::vector<NativeBindingInfo>;
    auto supportedComponents() const -> std::vector<ComponentInfo>;

private:
    NativeBindings m_bindings;
};

} // namespace Blade::Backend
