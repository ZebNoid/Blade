#include "Materializer.h"

#include "Runtime/Materializer/MaterializerCommands/MaterializerCommands.h"

namespace Blade {

auto Materializer::create(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    createNode(widgetTree, layoutTree, commands);

    return commands;
}

auto Materializer::update(const WidgetTree& widgetTree, const LayoutNode& layoutTree, bool includeRoot) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    updateNode(widgetTree, layoutTree, commands, Api::InvalidId, includeRoot);

    return commands;
}


auto Materializer::createNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent
) -> void
{
    if (layout.layoutType == LayoutType::None)
    {
        out.push_back(MaterializerCommands::Create(widget, parent));

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

    for (size_t i = 0; i < widget.children.size(); ++i)
    {
        createNode(widget.children[i], layout.children[i], out, parent);
    }
}

auto Materializer::updateNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (layout.layoutType == LayoutType::None)
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

} // namespace
