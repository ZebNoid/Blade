#include "Materializer.h"

#include "Runtime/Materializer/MaterializerCommands/MaterializerCommands.h"
#include "Runtime/Materializer/MenuMaterializer/MenuMaterializer.h"

namespace Blade {

namespace {

auto IsContextArea(const WidgetTree& widget) -> bool
{
    return widget.type == L"ContextArea";
}

auto HasEvent(const WidgetTree& widget, Api::Events event) -> bool
{
    return widget.events.find(event) != widget.events.end();
}

auto HasNativeDescendant(const WidgetTree& widget) -> bool
{
    if (widget.layoutType == LayoutType::None) return true;

    for (const auto& child : widget.children)
    {
        if (HasNativeDescendant(child)) return true;
    }

    return false;
}

auto IsNativeContextArea(const WidgetTree& widget) -> bool
{
    return IsContextArea(widget) && !widget.children.empty() && !HasNativeDescendant(widget.children.front());
}

auto ShouldMaterialize(const WidgetTree& widget, const LayoutNode& layout) -> bool
{
    return layout.layoutType == LayoutType::None || IsNativeContextArea(widget);
}

auto ShouldMaterialize(const WidgetTree& widget) -> bool
{
    return widget.layoutType == LayoutType::None || IsNativeContextArea(widget);
}

auto CreateCommand(
    const WidgetTree& widget,
    Api::Id parent,
    const std::vector<WidgetTree>* contextMenus,
    Api::Id dropTarget
) -> Api::ElementCommand
{
    auto command = MaterializerCommands::Create(widget, parent, MenuMaterializer::Build(contextMenus));
    if (dropTarget != Api::InvalidId && !HasEvent(widget, Api::Events::Drop)) command.props[Api::Props::DropTarget] = true;
    return command;
}

} // namespace

auto Materializer::create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    createNode(widgetTree, layoutTree, commands);

    return commands;
}

auto Materializer::update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    updateNode(widgetTree, layoutTree, commands, Api::InvalidId, includeRoot);

    return commands;
}

auto Materializer::remove(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    removeNode(widgetTree, commands);

    return commands;
}


auto Materializer::createNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    const std::vector<WidgetTree>* contextMenus,
    Api::Id dropTarget
) -> void
{
    const auto* ownContextMenus = !widget.overlays.empty() ? &widget.overlays : nullptr;
    const auto* activeContextMenus = contextMenus ? contextMenus : ownContextMenus;

    if (ShouldMaterialize(widget, layout))
    {
        out.push_back(CreateCommand(widget, parent, activeContextMenus, dropTarget));

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

    const auto isContextArea = IsContextArea(widget);
    const auto* childContextMenus = isContextArea ? &widget.overlays : nullptr;
    const auto childDropTarget = isContextArea && HasEvent(widget, Api::Events::Drop) ? widget.id : dropTarget;

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        createNode(widget.children[i], layout.children[i], out, parent, childContextMenus, childDropTarget);
    }
}

auto Materializer::updateNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (ShouldMaterialize(widget, layout))
    {
        if (includeCurrent)
        {
            out.push_back(MaterializerCommands::Update(layout, widget, parent));
        }

        currentParent = widget.id;
    }

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        updateNode(widget.children[i], layout.children[i], out, currentParent, true);
    }
}

auto Materializer::removeNode(const WidgetTree& widget, std::vector<Api::ElementCommand>& out) -> void
{
    for (const auto& child : widget.children)
    {
        removeNode(child, out);
    }

    for (const auto& overlay : widget.overlays)
    {
        removeNode(overlay, out);
    }

    if (ShouldMaterialize(widget))
    {
        out.push_back(MaterializerCommands::Remove(widget));
    }
}

} // namespace
