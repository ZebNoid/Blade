#include "MaterializerUpdate.h"

#include "Runtime/Materializer/MaterializerCommands/MaterializerCommands.h"
#include "Runtime/Materializer/MaterializerRules/MaterializerRules.h"

namespace Blade {

auto MaterializerUpdate::Build(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    updateNode(widgetTree, layoutTree, commands, Api::InvalidId, includeRoot);

    return commands;
}

auto MaterializerUpdate::BuildChanged(
    const WidgetTree& widgetTree,
    const LayoutNode& previousLayout,
    const LayoutNode& layoutTree,
    bool includeRoot
) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    updateChangedNode(widgetTree, &previousLayout, layoutTree, commands, Api::InvalidId, includeRoot);

    return commands;
}

auto MaterializerUpdate::updateNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (MaterializerRules::ShouldMaterialize(widget, layout))
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

auto MaterializerUpdate::updateChangedNode(
    const WidgetTree& widget,
    const LayoutNode* previousLayout,
    const LayoutNode& layout,
    std::vector<Api::ElementCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (MaterializerRules::ShouldMaterialize(widget, layout))
    {
        if (includeCurrent && !MaterializerRules::SameRect(previousLayout, layout))
        {
            out.push_back(MaterializerCommands::Update(layout, widget, parent));
        }

        currentParent = widget.id;
    }

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        const auto* previousChild = previousLayout && i < previousLayout->children.size() ? &previousLayout->children[i] : nullptr;
        updateChangedNode(widget.children[i], previousChild, layout.children[i], out, currentParent, true);
    }
}

} // namespace Blade
