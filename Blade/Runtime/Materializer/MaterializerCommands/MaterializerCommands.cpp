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
        .props = RectProps(layout, widget, parent)
    };
}

auto MaterializerCommands::RectProps(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::PropertyMap
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

} // namespace Blade
