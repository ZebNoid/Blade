#include "MaterializerCommands.h"

#include "Runtime/EventRuntime/EventSubscriptions.h"


namespace Blade {

auto MaterializerCommands::Create(const WidgetTree& widget, Api::Id parent) -> Api::ElementCommand
{
    return {
        .command = Api::ElementCommandType::Create,
        .id = widget.id,
        .parent = parent,
        .nodeType = widget.type,
        .props = widget.backend.create,
        .events = ToEventSubscriptions(widget.events)
    };
}

auto MaterializerCommands::Create(const WidgetTree& widget, Api::Id parent, const Api::ContextMenus& menus) -> Api::ElementCommand
{
    auto command = Create(widget, parent);
    if (!menus.empty()) command.props[Api::Props::ContextMenus] = menus;
    return command;
}

auto MaterializerCommands::Attach(const WidgetTree& widget, Api::Id parent) -> Api::ElementCommand
{
    return {
        .command = Api::ElementCommandType::Attach,
        .id = widget.id,
        .parent = parent
    };
}

auto MaterializerCommands::Update(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::ElementCommand
{
    return {
        .command = Api::ElementCommandType::Update,
        .id = widget.id,
        .props = UpdateProps(layout, widget, parent)
    };
}

auto MaterializerCommands::Visible(const WidgetTree& widget) -> Api::ElementCommand
{
    Api::PropertyMap props{
        { Api::Props::Visible, VisibleValue(widget) }
    };

    if (const auto it = widget.backend.create.find(Api::Props::State); it != widget.backend.create.end())
    {
        props[Api::Props::State] = it->second;
    }

    return {
        .command = Api::ElementCommandType::Update,
        .id = widget.id,
        .props = std::move(props)
    };
}

auto MaterializerCommands::UpdateProps(const LayoutNode& layout, const WidgetTree& widget, Api::Id parent) -> Api::PropertyMap
{
    Api::PropertyMap props;
    auto rect = layout.rect;

    if (parent == Api::InvalidId)
    {
        props[Api::Props::Size] = rect.size();

        if (const auto it = widget.backend.create.find(Api::Props::Placement); it != widget.backend.create.end())
        {
            props[Api::Props::Placement] = it->second;
        }

        if (const auto it = widget.backend.create.find(Api::Props::State); it != widget.backend.create.end())
        {
            props[Api::Props::State] = it->second;
        }

        return props;
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
