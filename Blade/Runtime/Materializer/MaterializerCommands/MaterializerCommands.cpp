#include "MaterializerCommands.h"

#include "Runtime/EventRuntime/EventSubscriptions.h"


namespace Blade {

auto MaterializerCommands::Create(const WidgetTree& widget, Api::Id parent) -> Api::BackendCommand
{
    return {
        .command = Api::CommandType::Create,
        .id = widget.id,
        .parent = parent,
        .nodeType = widget.type,
        .props = widget.backend.create,
        .events = ToEventSubscriptions(widget.events)
    };
}

auto MaterializerCommands::Attach(const WidgetTree& widget, Api::Id parent) -> Api::BackendCommand
{
    return {
        .command = Api::CommandType::Attach,
        .id = widget.id,
        .parent = parent
    };
}

auto MaterializerCommands::Update(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::BackendCommand
{
    return {
        .command = Api::CommandType::Update,
        .id = widget.id,
        .props = UpdateProps(layout, widget, parent)
    };
}

auto MaterializerCommands::Visible(const WidgetTree& widget) -> Api::BackendCommand
{
    return {
        .command = Api::CommandType::Update,
        .id = widget.id,
        .props = {
            { Api::Props::Visible, VisibleValue(widget) }
        }
    };
}

auto MaterializerCommands::UpdateProps(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::PropertyMap
{
    Api::PropertyMap props;
    auto rect = layout.rect;

    if (parent == Api::InvalidId)
    {
        rect.x = widget.layout.position.x;
        rect.y = widget.layout.position.y;
    }

    props[Api::Props::Rect] = rect;
    return props;
}

auto MaterializerCommands::VisibleValue(const WidgetTree& widget) -> bool
{
    const auto it = widget.backend.create.find(Api::Props::Visible);

    if (it == widget.backend.create.end())
    {
        return true;
    }

    const auto* visible = std::get_if<bool>(&it->second);
    return visible ? *visible : true;
}

} // namespace Blade
