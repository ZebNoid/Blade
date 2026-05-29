#include "MaterializerCreate.h"

#include "Runtime/Materializer/MaterializerCommands/MaterializerCommands.h"
#include "Runtime/Materializer/MaterializerRules/MaterializerRules.h"
#include "Runtime/Materializer/MenuMaterializer/MenuMaterializer.h"

namespace Blade {

namespace {

auto CreateCommand(
    const WidgetTree& widget,
    Api::Id parent,
    const std::vector<WidgetTree>* contextMenus,
    Api::Id dropTarget
) -> Api::ElementCommand
{
    auto command = MaterializerCommands::Create(widget, parent, MenuMaterializer::Build(contextMenus));
    if (dropTarget != Api::InvalidId && !MaterializerRules::HasEvent(widget, Api::Events::Drop)) command.props[Api::Props::DropTarget] = true;
    return command;
}

} // namespace

auto MaterializerCreate::Build(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    createNode(widgetTree, layoutTree, commands);

    return commands;
}

auto MaterializerCreate::createNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    MaterializerState state
) -> void
{
    const auto* ownContextMenus = !widget.overlays.empty() ? &widget.overlays : nullptr;
    const auto* activeContextMenus = state.contextMenus ? state.contextMenus : ownContextMenus;

    if (MaterializerRules::ShouldMaterialize(widget, layout))
    {
        out.push_back(CreateCommand(widget, parent, activeContextMenus, state.dropTarget));

        if (parent != Api::InvalidId)
        {
            out.push_back(MaterializerCommands::Attach(widget, parent));
        }

        out.push_back(MaterializerCommands::Update(layout, widget, parent));

        if (parent == Api::InvalidId)
        {
            out.push_back(MaterializerCommands::Visible(widget));
        }

        parent = widget.id;
    }

    const auto isContextArea = MaterializerRules::IsContextArea(widget);
    auto childState = state;
    if (isContextArea) childState.contextMenus = &widget.overlays;
    if (isContextArea && MaterializerRules::HasEvent(widget, Api::Events::Drop)) childState.dropTarget = widget.id;

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        createNode(widget.children[i], layout.children[i], out, parent, childState);
    }
}

} // namespace Blade
