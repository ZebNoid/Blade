#include "MaterializerRemove.h"

#include "Runtime/Materializer/MaterializerCommands/MaterializerCommands.h"
#include "Runtime/Materializer/MaterializerRules/MaterializerRules.h"

namespace Blade {

auto MaterializerRemove::Build(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>
{
    std::vector<Api::ElementCommand> commands;

    removeNode(widgetTree, commands);

    return commands;
}

auto MaterializerRemove::removeNode(const WidgetTree& widget, std::vector<Api::ElementCommand>& out) -> void
{
    for (const auto& child : widget.children)
    {
        removeNode(child, out);
    }

    for (const auto& overlay : widget.overlays)
    {
        removeNode(overlay, out);
    }

    if (MaterializerRules::ShouldMaterialize(widget))
    {
        out.push_back(MaterializerCommands::Remove(widget));
    }
}

} // namespace Blade
