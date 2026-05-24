#include "Materializer.h"

#include "Runtime/EventRuntime/EventSubscriptions.h"

namespace Blade {

auto Materializer::build(const WidgetTree& widgetTree, const LayoutNode& layoutTree) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    buildNode(widgetTree, layoutTree, commands);

    return commands;
}

auto Materializer::buildUpdates(
    const WidgetTree& widgetTree,
    const LayoutNode& layoutTree,
    bool includeRoot
) -> std::vector<Api::BackendCommand>
{
    std::vector<Api::BackendCommand> commands;

    buildUpdateNode(
        widgetTree,
        layoutTree,
        commands,
        Api::InvalidId,
        includeRoot
    );

    return commands;
}


auto Materializer::buildNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent
) -> void
{
    if (layout.isNative)
    {
        out.push_back({
            .command = Api::CommandType::Create,
            .id = widget.id,
            .parent = parent,
            .nodeType = widget.type,
            .props = widget.backend.create,
            .events = ToEventSubscriptions(widget.events)
        });

        if (parent != Api::InvalidId)
        {
            out.push_back({
                .command = Api::CommandType::Attach,
                .id = widget.id,
                .parent = parent
            });
        }

        auto props = buildRectProps(layout, widget, parent);

        out.push_back({
            .command = Api::CommandType::Update,
            .id = widget.id,
            .props = std::move(props)
        });

        parent = widget.id;
    }

    for (size_t i = 0;
         i < widget.children.size();
         ++i)
    {
        buildNode(
            widget.children[i],
            layout.children[i],
            out,
            parent
        );
    }
}

auto Materializer::buildUpdateNode(
    const WidgetTree& widget,
    const LayoutNode& layout,
    std::vector<Api::BackendCommand>& out,
    Api::Id parent,
    bool includeCurrent
) -> void
{
    Api::Id currentParent = parent;

    if (layout.isNative)
    {
        if (includeCurrent)
        {
            auto props = buildRectProps(layout, widget, parent);

            out.push_back({
                .command = Api::CommandType::Update,
                .id = widget.id,
                .props = std::move(props)
            });
        }

        currentParent = widget.id;
    }

    for (size_t i = 0;
         i < widget.children.size();
         ++i)
    {
        buildUpdateNode(
            widget.children[i],
            layout.children[i],
            out,
            currentParent,
            true
        );
    }
}

auto Materializer::buildRectProps(
    const LayoutNode& layout,
    const WidgetTree& widget,
    Api::Id parent
) -> Api::PropertyMap
{
    Api::PropertyMap props;

    if (parent == Api::InvalidId)
    {
        auto rect = layout.rect;
        rect.x = widget.layout.position.x;
        rect.y = widget.layout.position.y;

        props[Api::Props::Rect] = rect;
    }
    else
    {
        props[Api::Props::Rect] = layout.rect;
    }

    return props;
}

} // namespace
