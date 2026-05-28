#include "MenuMaterializer.h"

namespace Blade {

namespace {

auto GetProp(const Api::PropertyMap& map, Api::Props prop) -> const Api::PropertyValue*;
auto Trigger(const WidgetTree& menu) -> Api::MenuTrigger;
auto Title(const WidgetTree& item) -> Api::Text;

} // namespace

auto MenuMaterializer::Build(const std::vector<WidgetTree>* overlays) -> Api::ContextMenus
{
    Api::ContextMenus result;
    if (!overlays) return result;

    for (const auto& menu : *overlays)
    {
        Api::MenuData data{ .trigger = Trigger(menu) };

        for (const auto& item : menu.children)
        {
            data.items.push_back({
                .id = item.id,
                .title = Title(item)
            });
        }

        result.push_back(std::move(data));
    }

    return result;
}

namespace {

auto GetProp(const Api::PropertyMap& map, Api::Props prop) -> const Api::PropertyValue*
{
    const auto it = map.find(prop);
    return it == map.end() ? nullptr : &it->second;
}

auto Trigger(const WidgetTree& menu) -> Api::MenuTrigger
{
    const auto* value = GetProp(menu.backend.create, Api::Props::MenuTrigger);
    const auto* trigger = value ? std::get_if<Api::MenuTrigger>(value) : nullptr;
    return trigger ? *trigger : Api::MenuTrigger::RightClick;
}

auto Title(const WidgetTree& item) -> Api::Text
{
    const auto* value = GetProp(item.backend.create, Api::Props::Title);
    const auto* title = value ? std::get_if<Api::Text>(value) : nullptr;
    return title ? *title : L"";
}

} // namespace

} // namespace Blade
