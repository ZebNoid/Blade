#include "NativeBindingRegistry.h"

#include "UI/UI.h"

namespace Blade::Backend {

namespace {

auto DefaultBindings() -> NativeBindings
{
    return {
        { Api::WidgetTypes::Window, UI::Window },
        { Api::WidgetTypes::Button, UI::Button },
        { Api::WidgetTypes::Label, UI::Label },
        { Api::WidgetTypes::Image, UI::ImageSurface },
        { Api::WidgetTypes::ContextArea, UI::Surface },
        { Api::WidgetTypes::Tray, UI::Tray },
    };
}

auto SupportedComponents() -> std::vector<ComponentInfo>
{
    return {
        { UI::Window, L"Window" },
        { UI::Tray, L"Tray" },
        { UI::Button, L"Button" },
        { UI::Label, L"LabelSurface" },
        { UI::LabelNative, L"LabelNative" },
        { UI::ImageSurface, L"ImageSurface" },
        { UI::Surface, L"Surface" },
    };
}

} // namespace

auto NativeBindingRegistry::bind(Api::WidgetType widget, Api::ComponentType component) -> void
{
    m_bindings.insert_or_assign(widget, component);
}

auto NativeBindingRegistry::bind(const NativeBindings& bindings) -> void
{
    for (const auto& [widget, component] : bindings)
    {
        bind(widget, component);
    }
}

auto NativeBindingRegistry::resolve(Api::WidgetType widget) const -> Api::ComponentType
{
    const auto it = m_bindings.find(widget);
    return it == m_bindings.end() ? Api::ComponentTypes::Unknown : it->second;
}

auto NativeBindingRegistry::defaultBindings() const -> std::vector<NativeBindingInfo>
{
    std::vector<NativeBindingInfo> result;

    for (const auto& [widget, component] : DefaultBindings())
    {
        result.push_back({widget, component});
    }

    return result;
}

auto NativeBindingRegistry::supportedComponents() const -> std::vector<ComponentInfo>
{
    return SupportedComponents();
}

} // namespace Blade::Backend
