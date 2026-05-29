#include "Materializer.h"

#include "Runtime/Materializer/MaterializerCreate/MaterializerCreate.h"
#include "Runtime/Materializer/MaterializerRemove/MaterializerRemove.h"
#include "Runtime/Materializer/MaterializerUpdate/MaterializerUpdate.h"

namespace Blade {

auto Materializer::create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::ElementCommand>
{
    return MaterializerCreate::Build(widgetTree, layoutTree);
}

auto Materializer::update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot) -> std::vector<Api::ElementCommand>
{
    return MaterializerUpdate::Build(widgetTree, layoutTree, includeRoot);
}

auto Materializer::updateChanged(
    const WidgetTree& widgetTree,
    const LayoutNode& previousLayout,
    const LayoutNode& layoutTree,
    bool includeRoot
) -> std::vector<Api::ElementCommand>
{
    return MaterializerUpdate::BuildChanged(widgetTree, previousLayout, layoutTree, includeRoot);
}

auto Materializer::remove(const WidgetTree& widgetTree) -> std::vector<Api::ElementCommand>
{
    return MaterializerRemove::Build(widgetTree);
}

} // namespace
